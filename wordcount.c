/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief wordcount.c reads words from file and prints occurence of each word in
 * the file.
 * @date 19.4.2022
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "htab.h"
#include "io.h"

#define MAX_LEN 127
#define SIZE 5

void print_pairs(htab_pair_t* pair) {
    printf("%s %d\n", pair->key, pair->value);
}

int main() {
    htab_t* h;
    FILE* file;
    int word_length;
    bool over_limit = false;
    htab_pair_t* pair;

    h = htab_init(SIZE);
    if (h == NULL) {
        error_exit("Chyba: chyba při alokaci místa pro tabulku");
    }

    file = stdin;

    char* word = malloc(sizeof(char) * 127);
    if (word == NULL) {
        htab_free(h);
        fclose(file);
        error_exit("Chyba při alokaci paměti pro slovo v wordcount.");
    }

    while ((word_length = read_word(word, MAX_LEN, file)) != EOF) {
        // printf("slovo: %s\n", word);
        pair = htab_lookup_add(h, word);
        if (pair == NULL) {
            free(word);
            htab_free(h);
            fclose(file);
            error_exit("Chyba při alokaci paměti pro prvek v tabulce.");
        }
        if (!word_length && !over_limit) {
            warning_msg("Chyba: slovo větší než implementační limit.");
            over_limit = true;
        }
        pair->value++;
    }

    htab_for_each(h, *print_pairs);
    // printf("arr size:%d\n", htab_bucket_count(h));
    // printf("number of elements: %d\n", htab_size(h));

    free(word);
    htab_free(h);
    fclose(file);
    return 0;
}