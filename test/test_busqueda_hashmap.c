#include <assert.h>
#include <stdio.h>
#include "../src/hashmap.h"
#include "../src/document.h"
#include "../src/query.h"
#include "../src/graph.h"

// Test 4: search() con hashmap y query válida

Document *search(HashMap *index, Query *query, Document *doc);

void t1_hashmap_search() {
    runningtest("t1_hashmap_search");
    {
        HashMap *index = hashmap_create(10);
        Document *doc = create_document(10, "Tema IA", "Esto trata sobre inteligencia artificial");

        hashmap_put(index, "inteligencia", doc);

        Query *query = query_from_string("inteligencia");

        Document *result = search(index, query, doc); // 'doc' como grafo dummy

        assert(result != NULL);
        assert(result->id == 10);

        free_query(query);
        free_hashmap(index);
    }
    successtest();
}

void test_hashmap_search() {
    running("test_hashmap_search");
    {
        t1_hashmap_search();
    }
    success();
}
