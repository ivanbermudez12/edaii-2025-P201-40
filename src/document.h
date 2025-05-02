#ifndef DOCUMENT_H
#define DOCUMENT_H


#include "link.h"


typedef struct Document {
    int id;
    char *title;
    char *body;
    Link *links;
    struct Document *next; // per llista enllaçada de documents
} Document;


Document *document_desserialize(char *path);
Document *load_documents_from_folder(const char *folder_path);
void print_document(Document *doc);
void free_document(Document *doc);
void free_documents(Document *head);


#endif

