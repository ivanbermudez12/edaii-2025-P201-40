#ifndef LINK_H
#define LINK_H

typedef struct Link {
  int id;
  struct Link *next;
} Link;

Link *LinksInit();
Link *add_link(Link *head, int id);
void free_links(Link *head);

#endif
