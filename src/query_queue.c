#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query_queue.h"

void init_query_queue(QueryQueue *q) {
    q->front = 0;
    q->size = 0;
}

void add_query(QueryQueue *q, const char *query) {
    int index = (q->front + q->size) % MAX_HISTORY;
    if (q->size == MAX_HISTORY) {
        free(q->queries[q->front]);
        q->front = (q->front + 1) % MAX_HISTORY;
        q->size--;
    }
    q->queries[index] = strdup(query);
    q->size++;
}

void print_query_history(QueryQueue *q) {
    printf("\nÚltimas %d consultas:\n", q->size);
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % MAX_HISTORY;
        printf("- %s\n", q->queries[index]);
    }
}

void free_query_queue(QueryQueue *q) {
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % MAX_HISTORY;
        free(q->queries[index]);
    }
}
