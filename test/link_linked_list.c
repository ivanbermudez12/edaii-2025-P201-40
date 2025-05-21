#include "../src/link.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>

void t1_lll() {
  runningtest("t1_lll");
  {
    Link *links = LinksInit();
    Link *new_link = malloc(sizeof(Link));
    new_link->id = 42;
    new_link->next = NULL;
    links->next = new_link;

    assert(links->next != NULL);
    assert(links->next->id == 42);

    free(new_link);
    free(links);
  }
  successtest();
}

void t2_lll() {
  runningtest("t2_lll");
  {
    Link *head = LinksInit();
    Link *a = malloc(sizeof(Link));
    a->id = 1;
    Link *b = malloc(sizeof(Link));
    b->id = 2;
    Link *c = malloc(sizeof(Link));
    c->id = 3;
    a->next = b;
    b->next = c;
    c->next = NULL;
    head->next = a;

    Link *cur = head->next;
    int count = 0;
    while (cur != NULL) {
      count++;
      cur = cur->next;
    }
    assert(count == 3);

    free(c);
    free(b);
    free(a);
    free(head);
  }
  successtest();
}

void t3_lll() {
  runningtest("t3_lll");
  {
    Link *head = LinksInit();
    assert(head != NULL);
    assert(head->next == NULL);
    free(head);
  }
  successtest();
}

void test_links_list() {
  running("test_links_list");
  {
    t1_lll();
    t2_lll();
    t3_lll();
  }
  success();
}
