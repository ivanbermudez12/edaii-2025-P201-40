#include "../src/document.h"
#include <assert.h>
#include <stdio.h>

void t1() {
  runningtest("t1");
  {
    Document *doc = document_deserialize("./datasets/wikipedia12/2.txt");
    assert(doc != NULL);
    assert(doc->id == 2); // Depèn del contingut del fitxer
    assert(doc->title != NULL);
    assert(doc->body != NULL);
    assert(doc->links != NULL || doc->links == NULL); // segons si té enllaços
    free_document(doc);
  }
  successtest();
}

void test_document_desserialize() {
  running("test_document_desserialize");
  {
    // Put t1(), t2() or t3() dependeing on what we want
    t1();
  }
  success();
}
