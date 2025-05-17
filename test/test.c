#include "sample_lib_test.c"
#include "utils.h"
#include "document_parcing.c"
#include "document_linked_list.c"
#include "link_linked_list.c"
#include "busqueda_linear_test.c"
#include "test_query.c"
#include <stdio.h>

int main() {
  {
    // Call all test modules you want to run here
    sample_lib_test();
    test_document_desserialize();
    test_document_list();
    test_links_list();
    test_query();
    test_hashmap();
  }
  allsuccess();
}