#include "document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <dirent.h>


Document *document_desserialize(char *path) {
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
    Link *links = LinksInit();


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


    fclose(f);
    return document;
}


void print_document(Document *doc) {
    printf("ID: %d\n", doc->id);
    printf("Title: %s\n", doc->title);
    printf("Body: %.100s...\n", doc->body);
    printf("Links: ");
    for (Link *l = doc->links; l != NULL; l = l->next) {
        printf("%d ", l->id);
    }
    printf("\n");
}


void free_document(Document *doc) {
    if (!doc) return;
    free(doc->title);
    free(doc->body);
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
        if (entry->d_type == DT_REG) {
            snprintf(path, sizeof(path), "%s/%s", folder_path, entry->d_name);
            Document *doc = document_desserialize(path);
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
