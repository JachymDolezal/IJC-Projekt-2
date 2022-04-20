#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "htab.h"
#include "io.h"

#define MAX_LEN 127
#define SIZE 49999
/*I chose this prime number because hashfunctions work better with primes
 and because 42 is the answer to everything.
*/

void print_pairs(htab_pair_t* pair) {
    printf("%s %d\n", pair->key, pair->value);
}

int main(int argc, char** argv) {
    htab_t* h;
    FILE* file;
    int word_length;
    bool over_limit = false;
    htab_pair_t* pair;

    h = htab_init(SIZE);
    if (h == NULL) {
        error_exit("Chyba: chyba při alokaci místa pro tabulku");
    }

    if (argc == 2) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            error_exit("Chyba: chyba při otevření souboru.");
        }
    } else {
        error_exit("Chyba: nepovolený počet argumentů.");
    }

    char* word = malloc(sizeof(char) * 127);

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

    free(word);
    htab_free(h);
    fclose(file);
    return 0;
}