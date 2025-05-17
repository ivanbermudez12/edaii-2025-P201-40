#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/hashmap.h"
#include "../src/document.h"

// Funció auxiliar per crear un document simulat
Document *create_document(const char *id, const char *body) {
    Document *doc = malloc(sizeof(Document));
    doc->id = atoi(id);
    doc->title = strdup("Títol test");
    doc->body = strdup(body);
    doc->links = NULL;
    doc->next = NULL;
    return doc;
}

void t1() {
    runningtest("t1 - hashmap_get con clave existente");

    {
        // Inicialitzar un hashmap
        HashMap map;
        map.capacity = 10;
        map.buckets = calloc(map.capacity, sizeof(HashMapEntry*));

        // Crear document
        Document *doc = create_document("1", "texto de prueba");

        // Crear entrada per la clau "test"
        HashMapEntry *entry = malloc(sizeof(HashMapEntry));
        entry->key = strdup("test");
        entry->documents = malloc(sizeof(Document*));
        entry->documents[0] = doc;
        entry->doc_count = 1;
        entry->next = NULL;

        // Assignar a bucket corresponent
        unsigned long hash = hash_function("test");
        unsigned int bucket = hash % map.capacity;
        map.buckets[bucket] = entry;

        // Provar la cerca
        int count = 0;
        Document **docs = hashmap_get(&map, "test", &count);

        assert(docs != NULL);
        assert(count == 1);
        assert(docs[0]->id == 1);
        assert(strcmp(docs[0]->body, "texto de prueba") == 0);

        // Alliberar memòria
        free(doc->title);
        free(doc->body);
        free(doc);
        free(entry->key);
        free(entry->documents);
        free(entry);
        free(map.buckets);
    }

    successtest();
}

void test_hashmap() {
    running("test_hashmap");
    {
        t1();
    }
    success();
}
