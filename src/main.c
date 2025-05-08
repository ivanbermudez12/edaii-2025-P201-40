#include "document.h"
#include "query.h"
#include "query_queue.h"
#include "sample_lib.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_QUERY_LEN 256

void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s\n", foo);
}

int main() {
  printf("*****************\nWelcome to EDA 2!\n*****************\n");

  // Ejemplo de uso de factorial
  printf("Factorial of 4 is %d\n", fact(4));

  // Ejemplo para probar memory leaks
  // createaleak();

  // Deserializar documento simple
  Document *doc = document_desserialize("./datasets/wikipedia12/2.txt");
  print_document(doc);
  free_document(doc);

  // Cargar todos los documentos
  printf("\nCargando todos los documentos:\n");
  Document *all_docs = load_documents_from_folder("./datasets/wikipedia12");

  for (Document *cur = all_docs; cur; cur = cur->next) {
    print_document(cur);
  }

  // Inicializar historial de queries
  QueryQueue history;
  init_query_queue(&history);

  // CLI para búsqueda
  char query_str[MAX_QUERY_LEN];

  while (1) {
    printf("\nIngrese su consulta (vacía para salir): ");
    if (!fgets(query_str, sizeof(query_str), stdin))
      break;
    query_str[strcspn(query_str, "\n")] = 0;

    if (strlen(query_str) == 0) {
      printf("Saliendo del programa.\n");
      break;
    }

    // Guardar en historial
    add_query(&history, query_str);
    print_query_history(&history);

    // Procesar query
    QueryNode *query = query_from_string(query_str);
    if (!query) {
      printf("Consulta inválida.\n");
      continue;
    }

    // Buscar coincidencias
    printf("\nResultados de búsqueda:\n");
    int count = 0;
    for (Document *cur = all_docs; cur && count < 5; cur = cur->next) {
      if (match_document(cur, query)) {
        print_document(cur);
        count++;
      }
    }

    if (count == 0) {
      printf("No se encontraron coincidencias.\n");
    }

    free_query(query);
  }

  free_query_queue(&history);
  free_documents(all_docs);

  return 0;
}
