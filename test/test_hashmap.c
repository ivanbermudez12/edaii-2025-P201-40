#include <assert.h>
#include <stdio.h>
#include "../src/hashmap.h"
#include "../src/document.h"
#include "../src/query.h"
#include "../src/graph.h"
// Test 1: hashmap_get con clave inexistente
void t1_hashmap() {
    runningtest("t1_hashmap");
    {
        HashMap *map = hashmap_create(10);
        int count = 0;
        Document **result = hashmap_get(map, "inexistente", &count);
        assert(result == NULL);
        assert(count == 0);
        hashmap_free(map);
    }
    successtest();
}

// Test 2: hashmap_get con colisión (misma bucket)
void t2_hashmap() {
    runningtest("t2_hashmap");
    {
        HashMap *map = hashmap_create(2); // Muy baja capacidad -> más colisiones


        Document doc1 = {.id = 1, .title = "titulo1", .body = "contenido1"};
        Document doc2 = {.id = 2, .title = "titulo2", .body = "contenido2"};


        hashmap_add(map, "clave1", &doc1);
        hashmap_add(map, "clave2", &doc2);


        int count1 = 0, count2 = 0;
        Document **docs1 = hashmap_get(map, "clave1", &count1);
        Document **docs2 = hashmap_get(map, "clave2", &count2);


        assert(count1 == 1 && docs1[0] == &doc1);
        assert(count2 == 1 && docs2[0] == &doc2);


        hashmap_free(map);
    }
    successtest();
}


// Test 3: hashmap_get tras insertar múltiples documentos en la misma clave
void t3_hashmap() {
    runningtest("t3_hashmap");
    {
        HashMap *map = hashmap_create(10);


        Document doc1 = {.id = 1, .title = "titulo1", .body = "contenido1"};
        Document doc2 = {.id = 2, .title = "titulo2", .body = "contenido2"};


        hashmap_add(map, "python", &doc1);
        hashmap_add(map, "python", &doc2);  // misma clave


        int count = 0;
        Document **docs = hashmap_get(map, "python", &count);
        assert(count == 2);
       
        assert((docs[0] == &doc1 && docs[1] == &doc2) ||
               (docs[0] == &doc2 && docs[1] == &doc1));


        hashmap_free(map);
    }
    successtest();
}


// Función que ejecuta todos los tests de hashmap
void test_hashmap() {
    running("test_hashmap");
    {
        t1_hashmap();
        t2_hashmap();
        t3_hashmap();
    }
    success();
}
