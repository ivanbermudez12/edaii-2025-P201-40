#ifndef DOCUMENT_H
#define DOCUMENT_H


#include "link.h"
#include "query.h"


typedef struct Document {
    int id;
    char *title;
    char *body;
    Link *links;
    struct Document *next; // per llista enllaçada de documents
    char *content; // LAB 2
} Document;

// LAB 2
// Funciones para manejar los documentos
int contains_all_keywords(Document *doc, QueryNode *query);
void search_documents(Document *docs[], int num_docs, QueryNode *query);


Document *document_desserialize(char *path);
Document *load_documents_from_folder(const char *folder_path);
void print_document(Document *doc);
void free_document(Document *doc);
void free_documents(Document *head);

#endif


