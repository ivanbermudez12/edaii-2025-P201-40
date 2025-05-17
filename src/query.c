// LAB 2
#include "query.h"
#include "document.h"
#include "hashmap.h"
#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QueryNode *initialize_query(const char *query_str) {
  QueryNode *head = NULL, *tail = NULL;
  char *query_copy = strdup(query_str);
  char *token = strtok(query_copy, " ");

  while (token != NULL) {
    QueryNode *new_node = (QueryNode *)malloc(sizeof(QueryNode));
    new_node->keyword = strdup(token);
    new_node->next = NULL;

    if (head == NULL) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }

    token = strtok(NULL, " ");
  }

  free(query_copy);
  return head;
}

bool match_document(Document *doc, QueryNode *query) {
  bool current_or_group = false;
  bool has_or = false;
  bool or_matched = false;

  for (QueryNode *q = query; q != NULL; q = q->next) {
    if (strcmp(q->keyword, "|") == 0) {
      has_or = true;
      if (current_or_group)
        or_matched = true;
      current_or_group = false;
    } else if (q->keyword[0] == '-') {
      if (strstr(doc->body, q->keyword + 1))
        return false;
    } else {
      if (strstr(doc->body, q->keyword))
        current_or_group = true;
      else if (!has_or)
        return false;
    }
  }

  return has_or ? or_matched || current_or_group : true;
}


// Crea una Query a partir de un string (separado por espacios)
Query* query_from_string(const char* str) {
    if (str == NULL || strlen(str) == 0) return NULL;

    Query* query = malloc(sizeof(Query));
    if (!query) return NULL;
    query->head = parse_query_nodes(str);;

    char* input = strdup(str); // Copia porque strtok modifica
    char* token = strtok(input, " ");

    QueryNode* last = NULL;

    while (token != NULL) {
        QueryNode* node = malloc(sizeof(QueryNode));
        if (!node) break;

        node->keyword = strdup(token);  // Copia la palabra
        node->is_excluded = (token[0] == '-');
        node->next = NULL;

        if (!query->head) {
            query->head = node;
        } else {
            last->next = node;
        }

        last = node;
        token = strtok(NULL, " ");
    }
    

    free(input);
    return query;
}

// Libera la memoria de una Query
void query_free(Query* query) {
    if (query == NULL) return;
    
    QueryNode *current = query->head;
    while (current != NULL) {
        QueryNode *temp = current;
        current = current->next;
        free(temp->keyword);
        free(temp);
    }
    free(query);
}

Document *sort_by_relevance(Document *results, Document *graph) {
    if (!results || !graph) return NULL;
    
    // Implementación de ordenación por relevancia (usando bubble sort)
    int swapped;
    Document *ptr1;
    Document *lptr = NULL;
    
    // Verificar lista vacía
    if (results == NULL)
        return NULL;
    
    do {
        swapped = 0;
        ptr1 = results;
        
        while (ptr1->next != lptr) {
            float score1 = graph_get_indegree(graph, ptr1->id);
            float score2 = graph_get_indegree(graph, ptr1->next->id);
            
            if (score1 < score2) {
                // Intercambiar nodos
                Document *temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;
                
                if (ptr1 == results) {
                    results = temp;
                } else {
                    // Necesitamos encontrar el nodo anterior
                    Document *prev = results;
                    while (prev->next != ptr1) {
                        prev = prev->next;
                    }
                    prev->next = temp;
                }
                
                swapped = 1;
            } else {
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);
    
    return results;
}


Document *search(HashMap *index, Query *query, Document *graph) {
    if (!index || !query || !graph) return NULL;
    
    Document *results = NULL;
    QueryNode *current = query->head;
    
    while (current) {
        int count = 0;
        Document **docs = hashmap_get(index, current->keyword, &count);
        
        if (docs) {
            for (int i = 0; i < count; i++) {
                if (match_document(docs[i], query->head)) {
                    // Agregar documento a resultados
                    docs[i]->next = results;
                    results = docs[i];
                }
            }
        }
        
        current = current->next;
    }
    
    return sort_by_relevance(results, graph);
}

// Implementar funcion
Document **hashmap_get(HashMap *map, const char *key, int *count) {
    if (!map || !key || !count) return NULL;
    *count = 0;
    
    unsigned long hash = hash_function(key);
    unsigned int bucket = hash % map->capacity;
    
    HashMapEntry *entry = map->buckets[bucket];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            *count = entry->doc_count;
            return entry->documents;
        }
        entry = entry->next;
    }
    
    return NULL;
}