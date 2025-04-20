#include "document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <dirent.h>


void LinksAdd(Link** links, int link_id) {
    Link* new_link = (Link*)malloc(sizeof(Link));
    new_link->id = link_id;
    new_link->next = *links;
    *links = new_link;
}


Document* document_deserialize(char* path) {
    FILE* f = fopen(path, "r");
    assert(f != NULL);
   
    Document* document = (Document*)malloc(sizeof(Document));
   
    char buffer[262144];
    int bufferSize = 262144;
    int bufferIdx = 0;
    char ch;
    bufferIdx = 0;


    // ID
    while ((ch = fgetc(f)) != '\n') {
        assert(bufferIdx < bufferSize);
        buffer[bufferIdx++] = ch;
    }
    assert(bufferIdx < bufferSize);
    buffer[bufferIdx++] = '\0';
    document->id = atoi(buffer);


    // Title
    bufferIdx = 0;
    while ((ch = fgetc(f)) != '\n') {
        assert(bufferIdx < bufferSize);
        buffer[bufferIdx++] = ch;
    }
    buffer[bufferIdx] = '\0';
    document->title = strdup(buffer);


    // Body + links
    char linkBuffer[64];
    int linkBufferSize = 64;
    int linkBufferIdx = 0;
    bool parsingLink = false;


    bufferIdx = 0;


    while ((ch = fgetc(f)) != EOF) {
        assert(bufferIdx < bufferSize);
        buffer[bufferIdx++] = ch;


        if (parsingLink) {
            if (ch == ')') {
                parsingLink = false;
                assert(linkBufferIdx < linkBufferSize);
                linkBuffer[linkBufferIdx++] = '\0';
                int linkId = atoi(linkBuffer);


                LinksAdd(&(document->links), linkId);
                linkBufferIdx = 0;


            } else if (ch != '(') {
                assert(linkBufferIdx < linkBufferSize);
                linkBuffer[linkBufferIdx++] = ch;
            }
        } else if (ch == ']') {
            parsingLink = true;
        }
    }
    assert(bufferIdx < bufferSize);
    buffer[bufferIdx] = '\0';


    char *body = (char *)malloc(sizeof(char) * bufferIdx);
    strcpy(body, buffer);


    document->body = strdup(buffer);


    fclose(f);
    return document;
}


void print_document(Document* doc) {
    //printf("ID: %d\n", doc->id);
    printf("Title: %s\n", doc->title);
    //printf("Body: %.80s...\n", doc->body);
    //printf("Links:");
    Link* l = doc->links;
    while (l) {
        printf(" %d", l->id);
        l = l->next;
    }
    //printf("\n\n");
}


Document* load_documents_from_folder(char* folder_path) {
    DIR* dir = opendir(folder_path);
    if (!dir) {
        perror("opendir");
        return NULL;
    }


    struct dirent* entry;
    Document* head = NULL;
    Document* last = NULL;


    char filepath[512];


    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;


        snprintf(filepath, sizeof(filepath), "%s/%s", folder_path, entry->d_name);
        Document* doc = document_deserialize(filepath);


        if (doc) {
            if (!head) {
                head = doc;
                last = doc;
            } else {
                last->next = doc;
                last = doc;
            }
        }else {
            fprintf(stderr, "No s'ha pogut deserialitzar: %s\n", filepath);
        }
    }


    closedir(dir);
    return head;
}


