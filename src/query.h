// LAB 2

#ifndef QUERY_H
#define QUERY_H
#include <stdbool.h>
#include "document.h"
#include "query_queue.h"


typedef struct QueryNode {
    char *keyword;
    struct QueryNode *next;
} QueryNode;

// Funciones relacionadas con la consulta
QueryNode* initialize_query(const char *query_str);
void free_query(QueryNode *query);

QueryNode* query_from_string(const char* str); // declaración de query_from_string
bool match_document(const Document* doc, QueryNode* query);


#endif
