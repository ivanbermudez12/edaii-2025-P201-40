#include "reverse_index.h"
#include "hashmap.h"
#include "document.h"
#include "parser.h"  // Para normalize_word()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUCKET_SIZE 16

// Función hash para strings (simplificada)
unsigned long string_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash;
}

ReverseIndex *reverse_index_init() {
    ReverseIndex *idx = malloc(sizeof(ReverseIndex));
    if (!idx) return NULL;
    
    idx->title_index = hashmap_create(INITIAL_BUCKET_SIZE, string_hash);
    idx->content_index = hashmap_create(INITIAL_BUCKET_SIZE, string_hash);
    idx->total_docs = 0;
    
    if (!idx->title_index || !idx->content_index) {
        reverse_index_free(idx);
        return NULL;
    }
    return idx;
}

void reverse_index_free(ReverseIndex *idx) {
    if (!idx) return;
    
    // Liberar todos los DocLists en los índices
    hashmap_iter_t tit_iter = hashmap_iter(idx->title_index);
    const char *key;
    while ((key = hashmap_next(idx->title_index, &tit_iter))) {
        DocList *list = hashmap_get(idx->title_index, key);
        doclist_free(list);
    }
    
    hashmap_iter_t cont_iter = hashmap_iter(idx->content_index);
    while ((key = hashmap_next(idx->content_index, &cont_iter))) {
        DocList *list = hashmap_get(idx->content_index, key);
        doclist_free(list);
    }
    
    hashmap_free(idx->title_index);
    hashmap_free(idx->content_index);
    free(idx);
}

static void add_word_to_index(HashMap *index, const char *word, int doc_id) {
    char *norm_word = normalize_word(word);
    if (!norm_word) return;
    
    DocList *list = hashmap_get(index, norm_word);
    if (!list) {
        list = doclist_create();
        hashmap_put(index, norm_word, list);
    }
    doclist_add(list, doc_id);
    free(norm_word);
}

void reverse_index_add_doc(ReverseIndex *idx, const Document *doc) {
    if (!idx || !doc) return;
    
    int doc_id = document_get_id(doc);
    const char *title = document_get_name(doc);
    const char *content = document_get_content(doc);
    
    // Indexar título (word → doc_id)
    char *title_copy = strdup(title);
    char *word = strtok(title_copy, " ");
    while (word) {
        add_word_to_index(idx->title_index, word, doc_id);
        word = strtok(NULL, " ");
    }
    free(title_copy);
    
    // Indexar contenido
    char *content_copy = strdup(content);
    word = strtok(content_copy, " ");
    while (word) {
        add_word_to_index(idx->content_index, word, doc_id);
        word = strtok(NULL, " ");
    }
    free(content_copy);
    
    idx->total_docs++;
}

DocList *search_with_barrels(const ReverseIndex *idx, const char *query) {
    if (!idx || !query) return NULL;
    
    DocList *results = doclist_create();
    Query *q = query_init_from_string(query);
    if (!q) return NULL;
    
    // 1. Buscar en títulos (alta prioridad)
    for (int i = 0; i < query_keyword_count(q); i++) {
        const char *keyword = query_get_keyword(q, i);
        char *norm_key = normalize_word(keyword);
        DocList *matches = hashmap_get(idx->title_index, norm_key);
        if (matches) doclist_merge(results, matches);
        free(norm_key);
    }
    
    // 2. Buscar en contenido (baja prioridad)
    for (int i = 0; i < query_keyword_count(q); i++) {
        const char *keyword = query_get_keyword(q, i);
        char *norm_key = normalize_word(keyword);
        DocList *matches = hashmap_get(idx->content_index, norm_key);
        if (matches) doclist_merge(results, matches);
        free(norm_key);
    }
    
    query_free(q);
    return results;
}

// Funciones de serialización (formato binario)
void reverse_index_save(const ReverseIndex *idx, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return;
    
    // Guardar title_index
    hashmap_iter_t iter = hashmap_iter(idx->title_index);
    const char *key;
    while ((key = hashmap_next(idx->title_index, &iter))) {
        DocList *list = hashmap_get(idx->title_index, key);
        size_t key_len = strlen(key);
        fwrite(&key_len, sizeof(size_t), 1, file);
        fwrite(key, sizeof(char), key_len, file);
        doclist_serialize(list, file);
    }
    
    // Guardar content_index (mismo formato)
    iter = hashmap_iter(idx->content_index);
    while ((key = hashmap_next(idx->content_index, &iter))) {
        DocList *list = hashmap_get(idx->content_index, key);
        size_t key_len = strlen(key);
        fwrite(&key_len, sizeof(size_t), 1, file);
        fwrite(key, sizeof(char), key_len, file);
        doclist_serialize(list, file);
    }
    
    fclose(file);
}

ReverseIndex *reverse_index_load(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;
    
    ReverseIndex *idx = reverse_index_init();
    if (!idx) {
        fclose(file);
        return NULL;
    }
    
    size_t key_len;
    while (fread(&key_len, sizeof(size_t), 1, file) == 1) {
        char *key = malloc(key_len + 1);
        fread(key, sizeof(char), key_len, file);
        key[key_len] = '\0';
        
        DocList *list = doclist_deserialize(file);
        if (!list) {
            free(key);
            continue;
        }
        
        // Determinar a qué índice pertenece (simplificación)
        HashMap *target = (rand() % 2) ? idx->title_index : idx->content_index;
        hashmap_put(target, key, list);
        free(key);
    }
    
    fclose(file);
    return idx;
}