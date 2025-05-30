#ifndef GRAPH_H
#define GRAPH_H

#include "document.h"

typedef struct GraphNode {
  int doc_id;                   // ID del documento
  struct GraphNode **in_links;  // Documentos que enlazan a este
  int in_degree;                // Grado de entrada (relevancia)
  struct GraphNode **out_links; // Documentos enlazados desde este
  int out_degree;
} GraphNode;


typedef struct {
  GraphNode **nodes;
  int size;
  int capacity;
} DocumentGraph;

DocumentGraph *graph_create(int capacity);
void graph_add_link(DocumentGraph *graph, int from_doc_id, int to_doc_id);
float graph_get_indegree(DocumentGraph *graph, int doc_id);
void graph_free(DocumentGraph *graph, int doc_id);

#endif