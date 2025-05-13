// LAB 2

#ifndef QUERY_H
#define QUERY_H

// Agrega esta línea antes de usar 'Document'
typedef struct Document Document;

#include "query_queue.h"
#include <stdbool.h>

typedef struct QueryNode {
    char *keyword;
    struct QueryNode *next;
} QueryNode;

// Funciones relacionadas con la consulta
QueryNode *initialize_query(const char *query_str);
void free_query(QueryNode *query);
QueryNode *query_from_string(const char *str);

bool match_document(Document *doc, QueryNode *query);



#endif
