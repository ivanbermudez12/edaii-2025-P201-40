#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "link.h"
#include "query.h"
#include <stdbool.h>

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
  float relevance; // Puntuación calculada
  struct Document *next;
  const char *text;
  // Nuevos campos para manejo de palabras
  Word *words;
  int word_count;
} Document;

// LAB 2
// Funciones para manejar los documentos
Document *document_deserialize(const char *path);
Document *load_documents_from_folder(const char *folder_path);
void print_document(const Document *doc);
void free_document(Document *doc);
void free_documents(Document *head);
bool match_document(Document *doc, struct QueryNode *query);
int contains_all_keywords(Document *doc, struct QueryNode *query);
int document_get_word_count(const Document *doc);
int document_get_word_frequency(const Document *doc, const char *word);
char *document_get_snippet(const Document *doc, const char *word, int context_lines);
const char *document_get_content(const Document *doc);

#endif
