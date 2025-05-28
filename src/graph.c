#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

static GraphNode* create_node(int doc_id) {
    GraphNode* node = malloc(sizeof(GraphNode));
    node->doc_id = doc_id;
    node->in_links = NULL;
    node->in_degree = 0;
    node->out_links = NULL;
    node->out_degree = 0;
    return node;
}

static GraphNode* find_node(DocumentGraph* graph, int doc_id) {
    for (int i = 0; i < graph->size; i++) {
        if (graph->nodes[i]->doc_id == doc_id) {
            return graph->nodes[i];
        }
    }
    return NULL;
}

static void add_node(DocumentGraph* graph, GraphNode* node) {
    if (graph->size >= graph->capacity) {
        graph->capacity *= 2;
        graph->nodes = realloc(graph->nodes, graph->capacity * sizeof(GraphNode*));
    }
    graph->nodes[graph->size++] = node;
}

static void add_link(GraphNode*** links, int* degree, GraphNode* node) {
    *links = realloc(*links, (*degree + 1) * sizeof(GraphNode*));
    (*links)[(*degree)++] = node;
}

DocumentGraph* create_graph(int capacity) {
    DocumentGraph* graph = malloc(sizeof(DocumentGraph));
    graph->nodes = malloc(capacity * sizeof(GraphNode*));
    graph->size = 0;
    graph->capacity = capacity;
    return graph;
}

void graph_add_link(DocumentGraph *graph, int from_doc_id, int to_doc_id) {
    GraphNode* from_node = find_node(graph, from_doc_id);
    if (!from_node) {
        from_node = create_node(from_doc_id);
        add_node(graph, from_node);
    }

    GraphNode* to_node = find_node(graph, to_doc_id);
    if (!to_node) {
        to_node = create_node(to_doc_id);
        add_node(graph, to_node);
    }

    add_link(&from_node->out_links, &from_node->out_degree, to_node);
    add_link(&to_node->in_links, &to_node->in_degree, from_node);
}


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
}

void graph_free(DocumentGraph* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->size; i++) {
        GraphNode* node = graph->nodes[i];
        if (node->in_links) free(node->in_links);
        if (node->out_links) free(node->out_links);
        free(node);
    }

    free(graph->nodes);
    free(graph);

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
