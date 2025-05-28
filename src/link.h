#ifndef LINK_H
#define LINK_H

typedef struct Link {
  int id;
  int target_doc_id;
  char *anchor_text;
  struct Link *next;
} Link;

Link *LinksInit();
Link *add_link(Link *head, int target_doc_id);
void free_links(Link *head);

#endif
