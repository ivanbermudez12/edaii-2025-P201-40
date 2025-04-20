#include <stdlib.h>
#include <string.h>


typedef struct Link{
    int id;
    struct Link *next;
}Link;


Link *create_link(const char *url);