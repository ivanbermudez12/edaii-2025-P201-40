#ifndef HISTORY_H
#define HISTORY_H

#include "query.h"  // Asume que Query está definido en query.h

typedef struct {
    Query *queries[3];  // Buffer circular para 3 consultas
    int front;          // Índice de la consulta más antigua
    int count;          // Número de consultas almacenadas (0-3)
} QueryHistory;

// Crea/destruye el historial
QueryHistory *history_init();
void history_free(QueryHistory *h);

// Añade una consulta al historial (si ya hay 3, reemplaza la más antigua)
void history_push(QueryHistory *h, Query *q);

// Imprime las últimas 3 consultas (formato CLI)
void history_print(const QueryHistory *h);

#endif
