// LAB 2

#include "query.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QueryNode* initialize_query(const char *query_str) {
    QueryNode *head = NULL, *tail = NULL;
    char *query_copy = strdup(query_str);
    char *token = strtok(query_copy, " ");

    while (token != NULL) {
        QueryNode *new_node = (QueryNode*)malloc(sizeof(QueryNode));
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
