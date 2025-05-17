#ifndef QUERY_H
#define QUERY_H

#include <stdbool.h>
#include "document.h"

typedef struct Document Document;

typedef struct QueryNode {
    char* keyword;
    bool is_excluded;  // Para palabras con "-" (ej: -gatos)
    struct QueryNode* next;
} QueryNode;

typedef struct Query {
    QueryNode* head;
    QueryNode* tail;
    int size;
} Query;

// funciones
QueryNode *initialize_query(const char *query_str);
Query *query_from_string(const char *str);
QueryNode *parse_query_nodes(const char *str);
bool match_document(Document *doc, struct QueryNode *query);
void free_query(Query *query);
Document *sort_by_relevance(Document *results, DocumentGraph *graph);

#endif