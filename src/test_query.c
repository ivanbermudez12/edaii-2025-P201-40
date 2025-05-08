#include "document.h"
#include "query.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void test_query_init() {
  QueryNode *q = query_from_string("gato perro");
  assert(q != NULL);
  assert(strcmp(q->keyword, "gato") == 0);
  assert(strcmp(q->next->keyword, "perro") == 0);
  free_query(q);
  printf("test_query_init passed\n");
}

void test_query_exclusion() {
  QueryNode *q = query_from_string("gato -perro");
  Document d = {.body = "el gato duerme"};
  assert(match_document(&d, q) == true);
  d.body = "el gato y el perro";
  assert(match_document(&d, q) == false);
  free_query(q);
  printf("test_query_exclusion passed\n");
}

void test_or_conditions() {
  QueryNode *q = query_from_string("gato | perro");
  Document d = {.body = "el perro ladra"};
  assert(match_document(&d, q) == true);
  d.body = "el ratón";
  assert(match_document(&d, q) == false);
  free_query(q);
  printf("test_or_conditions passed\n");
}

int main() {
  test_query_init();
  test_query_exclusion();
  test_or_conditions();
  return 0;
}
