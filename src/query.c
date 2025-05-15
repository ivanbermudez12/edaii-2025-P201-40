// LAB 2
#include "query.h"
#include "document.h"
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


//nose si es necesario
QueryNode *parse_query_nodes(const char *str) {
    if (!str || !*str) return NULL;
    
    char *str_copy = strdup(str);
    if (!str_copy) return NULL;
    
    QueryNode *head = NULL, *tail = NULL;
    char *token = strtok(str_copy, " ");
    
    while (token != NULL) {
        QueryNode *new_node = malloc(sizeof(QueryNode));
        if (!new_node) {
            free(str_copy);
            // Liberar nodos ya creados (necesitarías una función para esto)
            return NULL;
        }
        
        new_node->keyword = strdup(token);
        new_node->next = NULL;
        
        if (!head) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        
        token = strtok(NULL, " ");
    }
    
    free(str_copy);
    return head;
}
//

// Crea una Query a partir de un string (separado por espacios)
Query* query_from_string(const char* str) {
    if (str == NULL || strlen(str) == 0) return NULL;

    Query* query = malloc(sizeof(Query));
    if (!query) return NULL;
    query->head = parse_query_nodes(str);;

    char* input = strdup(str); // Copia porque strtok modifica
    char* token = strtok(input, " ");

    QueryNode* last = NULL;

    while (token) {
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
void free_query(Query* query) {
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



