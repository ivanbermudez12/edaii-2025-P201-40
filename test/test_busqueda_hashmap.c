#include <assert.h>
#include <stdio.h>
#include "../src/hashmap.h"
#include "../src/document.h"
#include "../src/query.h"
#include "../src/graph.h"


// Test 4: search() con hashmap y query válida
void t1_hashmap_search() {
    runningtest("t1_hashmap_search");
    {
        HashMap *index = hashmap_create(10);
        Document *doc = malloc(sizeof(Document));
        *doc = (Document){
            .id = 10,
            .title = "Tema IA",
            .body = "Esto trata sobre inteligencia artificial"
        };


        hashmap_add(index, "inteligencia", doc);


        Query *query = query_from_string("inteligencia");
        assert(query != NULL);


        int count = 0;
        Document **results = hashmap_get(index, "inteligencia", &count);


        assert(results != NULL);
        assert(count == 1);
        assert(results[0]->id == 10);


        assert(match_document(doc, query->head) == true);


        free_query(query);
        hashmap_free(index);
        free(doc);
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
