#include <assert.h>
#include <stdio.h>
#include "../src/query.h"
#include "../src/document.h"

void t1_busqueda_lineal() {
    runningtest("t1_busqueda_lineal");
    {
        // Crear documento de prueba
        Document *doc = malloc(sizeof(Document));
        doc->id = 42;
        doc->title = strdup("Demo");
        doc->body = strdup("este es un ejemplo simple de búsqueda lineal");
        doc->links = NULL;
        doc->next = NULL;

        // Crear query que debe coincidir (todas las palabras están en el body)
        Query *query = query_from_string("ejemplo búsqueda");

        // match_document hace búsqueda lineal en el body
        bool match = match_document(doc, query->head);

        assert(match == true); // Debe coincidir

        // Ahora otra query que no debe coincidir
        Query *query2 = query_from_string("palabraInexistente");
        bool match2 = match_document(doc, query2->head);
        assert(match2 == false); // No coincide

        free(doc->title);
        free(doc->body);
        free(doc);
        query_free(query);
        query_free(query2);
    }
    successtest();
}


void test_busqueda_lineal() {
    running("test_busqueda_lineal");
    {
        t1_busqueda_lineal();
    }
    success();
}
