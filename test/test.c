#include "document_linked_list.c"
#include "document_parcing.c"
#include "link_linked_list.c"
#include "busqueda_linear_test.c"
#include "test_query.c"
#include "test_hashmap.c"
#include "test_busqueda_hashmap.c"
#include "sample_lib_test.c"
#include "graph_test.c"
#include <stdio.h>


int main() {
  {
    // Add HERE if there are more test modules
    //     |  |  |  |  |  |  |
    //     V  V  V  V  V  V  V
    sample_lib_test();
    test_document_desserialize();
    test_document_list();
    test_links_list();
    test_query_suite();
    test_busqueda_lineal();
    test_hashmap();
    test_hashmap_search();
    test_graph();
  }
  allsuccess();
}
