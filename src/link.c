#include "link.h"
#include <stdlib.h>

Link *LinksInit() { return NULL; }

Link *add_link(Link *head, int id) {
  Link *new_link = (Link *)malloc(sizeof(Link));
  new_link->id = id;
  new_link->next = head;
  return new_link;
}

void free_links(Link *head) {
  while (head) {
    Link *next = head->next;
    free(head);
    head = next;
  }
}
