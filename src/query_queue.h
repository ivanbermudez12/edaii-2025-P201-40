#ifndef QUERY_QUEUE_H
#define QUERY_QUEUE_H

#define MAX_HISTORY 3

typedef struct QueryQueue {
  char *queries[MAX_HISTORY];
  int front;
  int size;
} QueryQueue;

void init_query_queue(QueryQueue *q);
void add_query(QueryQueue *q, const char *query);
void print_query_history(QueryQueue *q);
void free_query_queue(QueryQueue *q);

#endif
