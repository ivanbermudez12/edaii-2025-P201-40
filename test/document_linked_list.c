#include "../src/document.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void t1_dll() {
  runningtest("t1_dll");
  {
    Document *doc1 = malloc(sizeof(Document));
    doc1->id = 1;
    doc1->title = strdup("Title 1");
    doc1->next = NULL;

    Document *doc2 = malloc(sizeof(Document));
    doc2->id = 2;
    doc2->title = strdup("Title 2");
    doc2->next = NULL;

    doc1->next = doc2;

    assert(doc1->id == 1);
    assert(strcmp(doc1->title, "Title 1") == 0);
    assert(doc1->next == doc2);
    assert(doc2->id == 2);

    free(doc1->title);
    free(doc2->title);
    free(doc2);
    free(doc1);
  }
  successtest();
}

void t2_dll() {
  runningtest("t2_dll");
  {
    Document *head = NULL;
    assert(head == NULL);
  }
  successtest();
}

void t3_dll() {
  runningtest("t3_dll");
  {
    Document *head = malloc(sizeof(Document));
    head->id = 1;
    head->title = strdup("Doc1");

    Document *middle = malloc(sizeof(Document));
    middle->id = 2;
    middle->title = strdup("Doc2");

    Document *last = malloc(sizeof(Document));
    last->id = 3;
    last->title = strdup("Doc3");

    head->next = middle;
    middle->next = last;
    last->next = NULL;

    Document *cur = head;
    int count = 0;
    while (cur != NULL) {
      count++;
      cur = cur->next;
    }
    assert(count == 3);

    free(head->title);
    free(head);
    free(middle->title);
    free(middle);
    free(last->title);
    free(last);
  }
  successtest();
}

void test_document_list() {
  running("test_document_list");
  {
    t1_dll();
    t2_dll();
    t3_dll();
  }
  success();
}
