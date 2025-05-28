#ifndef REVERSE_INDEX_H
#define REVERSE_INDEX_H

#include "document.h"  // Para DocList y Document
#include "hashmap.h"   // Asume implementación básica de HashMap

// Estructura principal del índice invertido con barrels (títulos vs. contenido)
typedef struct {
    HashMap *title_index;   // Palabras en títulos (alta prioridad)
    HashMap *content_index; // Palabras en contenido (baja prioridad)
    size_t total_docs;      // Número total de documentos indexados
} ReverseIndex;

// Inicializa/Libera el índice
ReverseIndex *reverse_index_init();
void reverse_index_free(ReverseIndex *idx);

// Añade palabras de un documento al índice
void reverse_index_add_doc(ReverseIndex *idx, 
                          const Document *doc);

// Búsqueda con barrels (títulos primero)
DocList *search_with_barrels(const ReverseIndex *idx, 
                            const char *query);

// Serialización (guardar/cargar desde archivo)
void reverse_index_save(const ReverseIndex *idx, 
                       const char *filename);
ReverseIndex *reverse_index_load(const char *filename);

// Normalización de palabras (para el parser)
char *normalize_word(const char *word);  // Elimina puntuación, lowercase, etc.

#endif