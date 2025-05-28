#include "history.h"
#include <stdio.h>
#include <stdlib.h>

QueryHistory *history_init() {
    QueryHistory *h = malloc(sizeof(QueryHistory));
    if (!h) return NULL;
    h->front = 0;
    h->count = 0;
    for (int i = 0; i < 3; i++) h->queries[i] = NULL;
    return h;
}

void history_free(QueryHistory *h) {
    if (!h) return;
    for (int i = 0; i < 3; i++) {
        if (h->queries[i]) query_free(h->queries[i]);  // Asume que query_free existe
    }
    free(h);
}

void history_push(QueryHistory *h, Query *q) {
    if (!h || !q) return;

    // Si hay 3 consultas, libera la más antigua
    if (h->count == 3) {
        query_free(h->queries[h->front]);
        h->queries[h->front] = NULL;
        h->front = (h->front + 1) % 3;
        h->count--;
    }

    // Añade la nueva consulta en la posición disponible
    int pos = (h->front + h->count) % 3;
    h->queries[pos] = q;
    h->count++;
}

void history_print(const QueryHistory *h) {
    if (!h || h->count == 0) {
        printf("No hay consultas recientes.\n");
        return;
    }

    printf("\n=== Últimas %d consultas ===\n", h->count);
    for (int i = 0; i < h->count; i++) {
        int pos = (h->front + i) % 3;
        printf("[%d] ", i + 1);
        query_print(h->queries[pos]);  // Asume que query_print existe
    }
}

