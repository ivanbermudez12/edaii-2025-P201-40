#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

HashMap *hashmap_create(int capacity) {
    HashMap *map = malloc(sizeof(HashMap));
    map->capacity = capacity;
    map->size = 0;
    map->buckets = calloc(capacity, sizeof(HashMapEntry*));
    return map;
}

void hashmap_add(HashMap *map, const char *key, Document *doc) {
    if (!map || !key || !doc) return;
    
    unsigned long hash = hash_function(key);
    unsigned int bucket = hash % map->capacity;
    HashMapEntry *entry = map->buckets[bucket];
    HashMapEntry *prev = NULL;
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            for (int i = 0; i < entry->doc_count; i++) {
                if (entry->documents[i]->id == doc->id) {
                    return;
                }
            }
            
            if (entry->doc_count >= entry->doc_capacity) {
                entry->doc_capacity *= 2;
                entry->documents = realloc(entry->documents, 
                                         entry->doc_capacity * sizeof(Document*));
            }
            entry->documents[entry->doc_count++] = doc;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
    
    HashMapEntry *new_entry = malloc(sizeof(HashMapEntry));
    new_entry->key = strdup(key);
    new_entry->documents = malloc(4 * sizeof(Document*));
    new_entry->documents[0] = doc;
    new_entry->doc_count = 1;
    new_entry->doc_capacity = 4;
    new_entry->next = NULL;
    
    if (prev) {
        prev->next = new_entry;
    } else {
        map->buckets[bucket] = new_entry;
    }
    map->size++;
}

void hashmap_free(HashMap *map) {
    if (!map) return;
    
    for (int i = 0; i < map->capacity; i++) {
        HashMapEntry *entry = map->buckets[i];
        while (entry) {
            HashMapEntry *next = entry->next;
            free(entry->key);
            free(entry->documents);
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    free(map);
}
