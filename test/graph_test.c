#include "../src/graph.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>


void t1_graph_basic_construction() {
    runningtest("t1_graph_basic_construction");


    // Crear grafo con capacidad inicial 2
    DocumentGraph *g = graph_create(2);
    assert(g != NULL);
    assert(g->size == 0);


    // Añadir un enlace de 1 → 2
    graph_add_link(g, 1, 2);
    assert(g->size == 2); // ahora debe tener 2 nodos


    // Añadir otro enlace 2 → 3
    graph_add_link(g, 2, 3);
    assert(g->size == 3); // debe haber 3 nodos


    // Verificar indegrees
    float indegree_1 = graph_get_indegree(g, 1);
    float indegree_2 = graph_get_indegree(g, 2);
    float indegree_3 = graph_get_indegree(g, 3);


    assert(indegree_1 == 0.0f);
    assert(indegree_2 == 1.0f); // 1 → 2
    assert(indegree_3 == 1.0f); // 2 → 3


    // Liberar recursos
    graph_free(g);


    successtest();
}


void test_graph() {
    running("test_graph");
    {
        t1_graph_basic_construction();
    }
    success();
}
