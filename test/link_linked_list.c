#include "../src/link.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>


void t1_lll() {
  runningtest("t1_lll");
  {
    Link *links = LinksInit();
    if (links == NULL) {
      fprintf(stderr, "Error: LinksInit returned NULL\n");
      exit(1);
    }


    Link *new_link = malloc(sizeof(Link));
    if (new_link == NULL) {
      fprintf(stderr, "Error: malloc failed\n");
      free(links);
      exit(1);
    }


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
    if (head == NULL) {
      fprintf(stderr, "Error: LinksInit returned NULL\n");
      return;
    }
   
    Link *a = malloc(sizeof(Link));
    Link *b = malloc(sizeof(Link));
    Link *c = malloc(sizeof(Link));
   
    if (!a || !b || !c) {
      fprintf(stderr, "Error: malloc failed\n");
      free(a); free(b); free(c); free(head);
      return;
    }
   
    a->id = 1;
    b->id = 2;
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
