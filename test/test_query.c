#include "../src/document.h"
#include "../src/query.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void t1_query_basic_parsing() {
    runningtest("t1_query_basic_parsing");
    {
        Query *q = query_from_string("gato perro");
        assert(q != NULL);
        assert(q->head != NULL);
        assert(strcmp(q->head->keyword, "gato") == 0);
        assert(q->head->next != NULL);
        assert(strcmp(q->head->next->keyword, "perro") == 0);
        free_query(q);
    }
    successtest();
}


void t2_query_exclusion_operator() {
    runningtest("t2_query_exclusion_operator");
    {
        Query *q = query_from_string("gato -perro");
        Document d = {.body = "el gato duerme"};
        assert(match_document(&d, q->head) == true);
       
        d.body = "el gato y el perro";
        assert(match_document(&d, q->head) == false);
       
        free_query(q);
    }
    successtest();
}


void t3_query_or_operator() {
    runningtest("t3_query_or_operator");
    {
        Query *q = query_from_string("perro | gato");
        Document d = {.body = "el perro ladra"};
        assert(match_document(&d, q->head) == true);
       
        d.body = "el ratón";
        assert(match_document(&d, q->head) == false);
       
        free_query(q);
    }
    successtest();
}


void test_query_suite() {
    running("test_query_suite");
    {
        t1_query_basic_parsing();
        t2_query_exclusion_operator();
        t3_query_or_operator();
    }
    success();
}