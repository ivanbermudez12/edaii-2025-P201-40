#include "document_linked_list.c"
#include "document_parcing.c"
#include "link_linked_list.c"
<<<<<<< HEAD
#include "busqueda_linear_test.c"
#include "test_query.c"
#include "test_hashmap.c"
#include "test_busqueda_hashmap.c"
=======
#include "sample_lib_test.c"
#include "test_query.c"
#include "utils.h"
>>>>>>> f304e36a4fa4191ba61f7652e964c80c6ced772e
#include <stdio.h>

int main() {
  {
    // Call all test modules you want to run here
    sample_lib_test();
    test_document_desserialize();
    test_document_list();
    test_links_list();
    test_query();
    test_busqueda_lineal();
    test_hashmap();
    test_hashmap_search();
  }
  allsuccess();
}