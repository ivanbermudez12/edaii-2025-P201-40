#include "sample_lib.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdbool.h>


#include "document.h"


void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}




int main() {
  //printf("*****************\nWelcome to EDA 2!\n*****************\n");


  // how to import and call a function
  //printf("Factorial of 4 is %d\n", fact(4));


  // uncomment and run "make v" to see how valgrind detects memory leaks
  // createaleak();


    Document* doc = document_deserialize("./datasets/wikipedia12/2.txt");
    print_document(doc);


    Document* docs = load_documents_from_folder("./datasets/wikipedia12");
    Document* current = docs;
    while (current) {
        printf("Títol: %s\n", current->title);
        current = current->next;
    }


    return 0;
}



// Prueba funco¡ionamiento pauuuuauauduihaifhioasfjvhiskdjghnwiesdghn PORFAVOR FUNCIONAAAAA
