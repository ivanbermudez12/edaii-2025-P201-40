#include "parser.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *normalize_word(const char *word) {
    if (!word) return NULL;

    // Reservamos memoria
    char *normalized = malloc(strlen(word) + 1);
    if (!normalized) return NULL;

    int j = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (isalpha((unsigned char)word[i])) {
            normalized[j++] = tolower((unsigned char)word[i]);
        }
    }
    normalized[j] = '\0';

    // Si no quedaron caracteres válidos
    if (j == 0) {
        free(normalized);
        return NULL;
    }

    return normalized;
}

void free_normalized_word(char *word) {
    free(word);  // free() es seguro con NULL
}