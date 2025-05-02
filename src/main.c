#include "sample_lib.h"
#include "document.h"
#include "query.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}


int main() {
  printf("*****************\nWelcome to EDA 2!\n*****************\n");


  // how to import and call a function
  printf("Factorial of 4 is %d\n", fact(4));


  // uncomment and run "make v" to see how valgrind detects memory leaks
  // createaleak();
  Document *doc = document_desserialize("./datasets/wikipedia12/2.txt");
    print_document(doc);
    free_document(doc);


    printf("\nCarregant tots els documents:\n");
    Document *all_docs = load_documents_from_folder("./datasets/wikipedia12");


    Document *cur = all_docs;
    while (cur) {
        print_document(cur);
        cur = cur->next;
    }


    free_documents(all_docs);
    return 0;

  // LAB 2
  Document *docs[3];
    docs[0] = (Document*)malloc(sizeof(Document));
    docs[0]->content = "Este es el primer documento con varias palabras clave.";

    docs[1] = (Document*)malloc(sizeof(Document));
    docs[1]->content = "El segundo documento tiene algunas palabras clave similares.";

    docs[2] = (Document*)malloc(sizeof(Document));
    docs[2]->content = "Este documento no tiene palabras clave.";

    char query_str[256];
    printf("Ingrese su consulta de búsqueda (palabras clave separadas por espacio): ");
    fgets(query_str, 256, stdin);

    query_str[strcspn(query_str, "\n")] = 0;  // Eliminar el salto de línea

    if (strlen(query_str) == 0) {
        printf("Saliendo del programa.\n");
        return 0;  // Salir si la consulta está vacía
    }

    QueryNode *query = initialize_query(query_str);
    search_documents(docs, 3, query);

    // Liberar memoria
    free_query(query);
    for (int i = 0; i < 3; i++) {
        free(docs[i]);
    }

    return 0;
}





