#include "document.h"
#include "query.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void t1_query() {
  runningtest("t1_query");
  {
    Query* q = query_from_string("gato perro");
    assert(strcmp(q->head->keyword, "gato") == 0);
    assert(strcmp(q->head->next->keyword, "perro") == 0);
    free_query(q);
  }
  successtest();
}

void t2_query() {
  runningtest("t2_query");
  {
    Query *q = query_from_string("gato -perro");
    Document d = {.body = "el gato duerme"};
    assert(match_document(&d, q) == true);
    d.body = "el gato y el perro";
    assert(match_document(&d, q) == false);
    free_query(q);
  }
  successtest();
}

void t3_query() {
  runningtest("t3_query");
  {
    Query *q = query_from_string("gato | perro");
    Document d = {.body = "el perro ladra"};
    assert(match_document(&d, q) == true);
    d.body = "el ratón";
    assert(match_document(&d, q) == false);
    free_query(q);
  }
  successtest();
}

void test_query() {
  running("test_query");
  {
    // Call all tests you want to run here
    t1_query();
    t2_query();
    t3_query();
  }
  success();
}