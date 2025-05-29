#define _DEFAULT_SOURCE
#include "document.h"
#include "query.h"
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Document *document_deserialize(const char *path) {
  FILE *f = fopen(path, "r");
  assert(f != NULL);

  Document *document = (Document *)malloc(sizeof(Document));
  document->next = NULL;

  char buffer[262144];
  int bufferIdx = 0;
  char ch;

  // parse id
  while ((ch = fgetc(f)) != '\n') {
    buffer[bufferIdx++] = ch;
  }
  buffer[bufferIdx] = '\0';
  document->id = atoi(buffer);

  // parse title
  bufferIdx = 0;
  while ((ch = fgetc(f)) != '\n') {
    buffer[bufferIdx++] = ch;
  }
  buffer[bufferIdx] = '\0';
  document->title = strdup(buffer);

  // parse body + links
  char linkBuffer[64];
  int linkBufferIdx = 0;
  bool parsingLink = false;
  Link *links = NULL;

  bufferIdx = 0;
  while ((ch = fgetc(f)) != EOF) {
    buffer[bufferIdx++] = ch;
    if (parsingLink) {
      if (ch == ')') {
        linkBuffer[linkBufferIdx] = '\0';
        int linkId = atoi(linkBuffer);
        links = add_link(links, linkId);
        parsingLink = false;
        linkBufferIdx = 0;
      } else if (ch != '(') {
        linkBuffer[linkBufferIdx++] = ch;
      }
    } else if (ch == ']') {
      parsingLink = true;
    }
  }
  buffer[bufferIdx] = '\0';
  document->body = strdup(buffer);
  document->links = links;
  document->relevance = 0.0f;

  fclose(f);
  return document;
}

void print_document(const Document *doc) {
  if (!doc)
    return;
  printf("ID: %d\n", doc->id);
  printf("Title: %s\n", doc->title);
  printf("Body: %.150s%s\n", doc->body, strlen(doc->body) > 150 ? "..." : "");
  printf("Relevance: %.2f\n", doc->relevance);
}

void free_document(Document *doc) {
  if (!doc)
    return;
  if (doc->title)
    free(doc->title);
  if (doc->body)
    free(doc->body);
  if (doc->links)
    free_links(doc->links);
  free(doc);
}

Document *load_documents_from_folder(const char *folder_path) {
  DIR *dir = opendir(folder_path);
  if (!dir) {
    perror("opendir");
    return NULL;
  }

  struct dirent *entry;
  char path[1024];
  Document *head = NULL;
  Document *tail = NULL;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.')
      continue; // Ignorar "." y ".."

    snprintf(path, sizeof(path), "%s/%s", folder_path, entry->d_name);

    // Comprobar que el archivo termine en ".txt"
    if (strstr(entry->d_name, ".txt") != NULL) {
      Document *doc = document_deserialize(path);
      if (!head) {
        head = doc;
        tail = doc;
      } else {
        tail->next = doc;
        tail = doc;
      }
    }
  }

  closedir(dir);
  return head;
}

void free_documents(Document *head) {
  while (head) {
    Document *next = head->next;
    free_document(head);
    head = next;
  }
}

// LAB 2

int contains_all_keywords(Document *doc, QueryNode *query) {
  QueryNode *current = query;
  while (current != NULL) {
    if (current->is_excluded) {
      if (strstr(doc->body, current->keyword + 1) != NULL) {
        return 0;
      }
    } else {
      if (strstr(doc->body, current->keyword) == NULL) {
        return 0;
      }
    }
    current = current->next;
  }
  return 1;
}

void search_documents(Document *docs[], int num_docs, QueryNode *query) {
  int count = 0;

  for (int i = 0; i < num_docs && count < 5; i++) {
    if (contains_all_keywords(docs[i], query)) {
      printf("Documento %d: %s\n", i + 1, docs[i]->body);
      count++;
    }
  }

  if (count == 0) {
    printf("No se encontraron documentos que contengan todas las palabras "
           "clave.\n");
  }
}

// Devuelve el número total de palabras en el documento
int document_get_word_count(const Document *doc) {
  int total = 0;
  for (int i = 0; i < doc->word_count; i++) {
    total += doc->words[i].count;
  }
  return total;
}

// Devuelve la frecuencia de una palabra específica
int document_get_word_frequency(const Document *doc, const char *word) {
  for (int i = 0; i < doc->word_count; i++) {
    if (strcmp(doc->words[i].text, word) == 0) {
      return doc->words[i].count;
    }
  }
  return 0;
}

char *document_get_snippet(const Document *doc, const char *word, int context_lines) {
    const char *content = document_get_content(doc);
    if (!content || !word) return NULL;

    // Normalizar palabra buscada (usando la misma función del parser)
    char *normalized_word = normalize_word(word);  // Asume que existe en parser.c
    if (!normalized_word) return NULL;

    // Buscar la primera aparición
    char *found = strstr(content, normalized_word);
    free(normalized_word);
    if (!found) return NULL;

    // Calcular posiciones inicial/final del snippet
    const char *start = content;
    const char *end = content + strlen(content);
    int lines_before = 0, lines_after = 0;

    // Retroceder `context_lines` líneas
    const char *ptr = found;
    while (ptr > start && lines_before < context_lines) {
        if (*ptr == '\n') lines_before++;
        ptr--;
    }
    start = ptr;

    // Avanzar `context_lines` líneas
    ptr = found;
    while (ptr < end && lines_after < context_lines) {
        if (*ptr == '\n') lines_after++;
        ptr++;
    }
    end = ptr;

    // Extraer y formatear snippet
    size_t len = end - start;
    char *snippet = malloc(len + 1);
    if (!snippet) return NULL;
    strncpy(snippet, start, len);
    snippet[len] = '\0';

    return snippet;
}

Document *create_document(int id, const char *title, const char *body) {
    Document *doc = malloc(sizeof(Document));
    if (!doc) return NULL;
    doc->id = id;
    doc->title = strdup(title);
    doc->body = strdup(body);
    doc->links = NULL;
    doc->relevance = 0.0f;
    doc->next = NULL;
    doc->words = NULL;
    doc->word_count = 0;
    return doc;
}
