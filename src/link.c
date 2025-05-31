#include "link.h"
#include <stdlib.h>

Link *LinksInit() {
    Link *head = malloc(sizeof(Link));
    if (head == NULL) {
        return NULL; // error en malloc
    }
    head->next = NULL;
    head->id = -1; // es opcional: -1 como valor centinela
    return head;
}

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
