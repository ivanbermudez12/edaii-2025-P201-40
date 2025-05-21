#include "link.h"
#include <stdlib.h>

Link *LinksInit() { return NULL; }

Link *add_link(Link *head, int target_doc_id) {
  Link *new_link = malloc(sizeof(Link));
  if (!new_link)
    return head;

  new_link->target_doc_id = target_doc_id;
  new_link->next = head;
  return new_link;
}

void free_links(Link *head) {
  while (head) {
    Link *temp = head;
    head = head->next;
    free(temp);
  }
}
