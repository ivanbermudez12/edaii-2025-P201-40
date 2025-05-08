// LAB 2
#include "query.h"
#include "document.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QueryNode *initialize_query(const char *query_str) {
  QueryNode *head = NULL, *tail = NULL;
  char *query_copy = strdup(query_str);
  char *token = strtok(query_copy, " ");

  while (token != NULL) {
    QueryNode *new_node = (QueryNode *)malloc(sizeof(QueryNode));
    new_node->keyword = strdup(token);
    new_node->next = NULL;

    if (head == NULL) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }

    token = strtok(NULL, " ");
  }

  free(query_copy);
  return head;
}

void free_query(QueryNode *query) {
  QueryNode *current = query;
  while (current != NULL) {
    QueryNode *temp = current;
    current = current->next;
    free(temp->keyword);
    free(temp);
  }
}


bool match_document(Document *doc, QueryNode *query) {
  bool current_or_group = false;
  bool has_or = false;
  bool or_matched = false;

  for (QueryNode *q = query; q != NULL; q = q->next) {
    if (strcmp(q->keyword, "|") == 0) {
      has_or = true;
      if (current_or_group)
        or_matched = true;
      current_or_group = false;
    } else if (q->keyword[0] == '-') {
      if (strstr(doc->body, q->keyword + 1))
        return false;
    } else {
      if (strstr(doc->body, q->keyword))
        current_or_group = true;
      else if (!has_or)
        return false;
    }
  }

  return has_or ? or_matched || current_or_group : true;
}