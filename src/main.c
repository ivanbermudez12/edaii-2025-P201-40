#include "document.h"
#include "graph.h"
#include "hashmap.h"
#include "query.h"
#include "query_queue.h"
#include "sample_lib.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_QUERY_LEN 256
#define MAX_RESULTS 5
#define MAX_HISTORY_DISPLAY 10

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void show_recent_searches(QueryQueue *history) {
    if (!history) return;
    
    printf("\n******** recent searches *******\n");
    for (int i = 0; i < history->size && i < MAX_HISTORY_DISPLAY; i++) {
        int idx = (history->front + i) % MAX_HISTORY;
        if (history->queries[idx]) {
            printf("* %s *\n", history->queries[idx]);
        }
    }
    printf("***************\n");
}

void print_search_result(Document *doc, int index) {
    if (!doc) return;
    
    printf("(%d) %s\n", index, doc->title ? doc->title : "No title");
    printf("---\n");
    
    const char *content = doc->body ? doc->body : (doc->text ? doc->text : "No content available");
    int content_len = content ? strlen(content) : 0;
    int snippet_len = content_len > 150 ? 150 : content_len;
    
    if (content_len > 0) {
        char snippet[151];
        strncpy(snippet, content, snippet_len);
        snippet[snippet_len] = '\0';
        printf("%s\n", snippet);
    }
    printf("---\n");
    
    float relevance = doc->relevance >= 0 ? doc->relevance : (doc->title ? strlen(doc->title) : 0);
    printf("relevance score: %.1f\n\n", relevance);
}

// Versión corregida de match_document que acepta Query*
bool match_document_query(Document *doc, Query *query) {
    if (!doc || !query || !query->head || !doc->body) {
        return false;
    }
    
    bool current_or_group = false;
    bool has_or = false;
    bool or_matched = false;

    for (QueryNode *q = query->head; q != NULL; q = q->next) {
        if (strcmp(q->keyword, "|") == 0) {
            has_or = true;
            if (current_or_group)
                or_matched = true;
            current_or_group = false;
        } 
        else if (q->is_excluded) {
            if (strstr(doc->body, q->keyword + 1))
                return false;
        } 
        else {
            if (strstr(doc->body, q->keyword))
                current_or_group = true;
            else if (!has_or)
                return false;
        }
    }

    return has_or ? (or_matched || current_or_group) : true;
}

int main() {
    clear_screen();
    printf("*****************\nWelcome to EDA 2 Search Engine!\n*****************\n");

    // Cargar todos los documentos
    Document *all_docs = load_documents_from_folder("./datasets/wikipedia12");
    if (!all_docs) {
        printf("Error loading documents.\n");
        return 1;
    }

    // Inicializar historial de queries
    QueryQueue history;
    init_query_queue(&history);

    // CLI interactivo
    char query_str[MAX_QUERY_LEN];

    while (1) {
        clear_screen();
        show_recent_searches(&history);
        
        printf("Search: ");
        if (!fgets(query_str, sizeof(query_str), stdin)){
            break;
        }
        query_str[strcspn(query_str, "\n")] = '\0';

        if (strlen(query_str) == 0) {
            printf("\nExiting program.\n");
            break;
        }

        // Guardar en historial
        add_query(&history, query_str);

        // Procesar query
        Query *query = query_from_string(query_str);
        if (!query) {
            printf("\nInvalid query. Press Enter to continue...");
            while (getchar() != '\n');
            continue;
        }

        // Buscar coincidencias
        clear_screen();
        show_recent_searches(&history);
        printf("Search: %s\n\n", query_str);

        int count = 0;
        for (Document *cur = all_docs; cur && count < MAX_RESULTS; cur = cur->next) {
            if (match_document_query(cur, query)) {
                print_search_result(cur, count);
                count++;
            }
        }

        if (count == 0) {
            printf("No results found for \"%s\"\n", query_str);
        } else {
            printf("\n[%d results]\n", count);
        }

        free_query(query);

        printf("\nPress Enter to continue...");
        while (getchar() != '\n');
    }

    free_query_queue(&history);
    free_documents(all_docs);
    return 0;
}
