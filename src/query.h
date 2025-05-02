// LAB 2

#ifndef QUERY_H
#define QUERY_H

typedef struct QueryNode {
    char *keyword;
    struct QueryNode *next;
} QueryNode;

// Funciones relacionadas con la consulta
QueryNode* initialize_query(const char *query_str);
void free_query(QueryNode *query);

#endif
