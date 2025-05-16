#include "graph.h"
#include <stdlib.h>

float graph_get_indegree(DocumentGraph *graph, int doc_id) {
    if (!graph || !graph->nodes) return 0.0f;
    
    for (int i = 0; i < graph->size; i++) {
        if (graph->nodes[i]->doc_id == doc_id) {
            return (float)graph->nodes[i]->in_degree;
        }
    }
    return 0.0f;
}