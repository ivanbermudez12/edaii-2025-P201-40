#include "graph.h"
#include <stdlib.h>

DocumentGraph *graph_create(int capacity) {
  DocumentGraph *graph = malloc(sizeof(DocumentGraph));
  if (!graph)
    return NULL;

  graph->nodes = calloc(capacity, sizeof(GraphNode *));
  if (!graph->nodes) {
    free(graph);
    return NULL;
  }

  graph->size = 0;
  graph->capacity = capacity;
  return graph;
}

float graph_get_indegree(DocumentGraph *graph, int doc_id) {
  if (!graph || !graph->nodes)
    return 0.0f;

  for (int i = 0; i < graph->size; i++) {
    if (graph->nodes[i]->doc_id == doc_id) {
      return (float)graph->nodes[i]->in_degree;
    }
  }
  return 0.0f;
}

void graph_free(DocumentGraph *graph) {
  if (!graph)
    return;

  for (int i = 0; i < graph->size; i++) {
    free(graph->nodes[i]->in_links);
    free(graph->nodes[i]->out_links);
    free(graph->nodes[i]);
  }
  free(graph->nodes);
  free(graph);
}
