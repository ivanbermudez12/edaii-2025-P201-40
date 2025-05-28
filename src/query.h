#ifndef QUERY_H
#define QUERY_H

#include "document.h"
#include "graph.h"
#include <stdbool.h>

typedef struct Document Document;
typedef struct QueryNode QueryNode;
typedef struct Query Query;

typedef struct QueryNode {
  char *keyword;
  bool is_excluded; // Para palabras con "-" (ej: -gatos)
  struct QueryNode *next;
} QueryNode;

typedef struct Query {
  QueryNode *head;
  QueryNode *tail;
  int size;
} Query;

// funciones
QueryNode *initialize_query(const char *query_str);
Query *query_from_string(const char *str);
QueryNode *parse_query_nodes(const char *query_string);
bool match_document(Document *doc, QueryNode *query);
void free_query(Query *query);
<<<<<<< HEAD
=======

struct DocumentGraph;
>>>>>>> f304e36a4fa4191ba61f7652e964c80c6ced772e
Document *sort_by_relevance(Document *results, DocumentGraph *graph);

#endif