#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "link.h"
#include "query.h"

struct QueryNode;

typedef struct {
    char *text;
    int count;
} Word;

typedef struct Document {
    int id;
    char *title;
    char *body;
    Link *links;
    struct Document *next;

    // Nuevos campos para manejo de palabras
    Word *words;
    int word_count;
} Document;


// LAB 2
// Funciones para manejar los documentos
int contains_all_keywords(Document *doc, struct QueryNode *query);
void search_documents(Document *docs[], int num_docs, struct QueryNode *query);

Document *document_desserialize(char *path);
Document *load_documents_from_folder(const char *folder_path);
void print_document(Document *doc);
void free_document(Document *doc);
void free_documents(Document *head);

int document_get_word_count(const Document* doc);
int document_get_word_frequency(const Document* doc, const char* word);


#endif
