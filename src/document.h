#ifndef DOCUMENT_H
#define DOCUMENT_H


#include "link.h"


typedef struct Document {
    int id;
    char* title;
    char* body;
    Link* links;
    struct Document* next;
} Document;


Document* document_deserialize(char* path);
Document* load_documents_from_folder(char* folder_path);
void print_document(Document* doc);
void LinksAdd(Link** links, int link_id);


#endif
