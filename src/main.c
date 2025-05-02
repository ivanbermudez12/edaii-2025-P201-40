#include "sample_lib.h"
#include "document.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


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
    Document *docs = load_documents_from_folder("./datasets/wikipedia12");


    Document *cur = docs;
    while (cur) {
        print_document(cur);
        cur = cur->next;
    }


    free_documents(docs);
    return 0;
}





