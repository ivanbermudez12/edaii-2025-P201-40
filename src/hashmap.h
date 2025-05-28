#ifndef HASHMAP_H
#define HASHMAP_H

#include "document.h"

typedef struct HashMapEntry {
  char *key;                 // Palabra clave (normalizada)
  Document **documents;      // Array de documentos
  int doc_count;             // Número de documentos
  int doc_capacity;          // Capacidad del array
  struct HashMapEntry *next; // Para manejar colisiones
} HashMapEntry;

typedef struct {
  HashMapEntry **buckets; // Array de buckets
  int size;               // Tamaño actual
  int capacity;           // Capacidad total
} HashMap;

// Funciones para el reverse-index
HashMap *hashmap_create(int capacity);
Document **hashmap_get(HashMap *map, const char *key, int *count);
void hashmap_free(HashMap *map);
unsigned long hash_function(const char *str);

#endif