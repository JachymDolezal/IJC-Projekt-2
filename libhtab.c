#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"

// v libhtab

typedef struct htab_item {
    htab_pair_t pair;
    htab_item* next;
} htab_item;

struct htab_t {
    htab_value_t size;
    htab_value_t arr_size;
    htab_item** arr_ptr;
};

// v htab.h

size_t htab_hash_function(htab_key_t str) {
    uint32_t hash = 0;
    unsigned char* p;

    for (p = (unsigned char*)str; *p != '\0'; p++) {
        hash = 65599 * hash + *p;
    }
    return hash;
}

// Funkce pro práci s tabulkou:
htab_t* htab_init(size_t n) {}
size_t htab_size(const htab_t* t) {}
size_t htab_bucket_count(const htab_t* t) {}
void htab_resize(htab_t* t, size_t newn) {}
// (umožňuje rezervaci místa)

htab_pair_t* htab_find(htab_t* t, htab_key_t key) {}
htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {}

bool htab_erase(htab_t* t, htab_key_t key) {
    return true;
}

// for_each: projde všechny záznamy a zavolá na ně funkci f
// Pozor: f nesmí měnit klíč .key ani přidávat/rušit položky
void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data)) {}

void htab_clear(htab_t* t) {}
void htab_free(htab_t* t) {}

int main() {
    int array_size = 10;

    printf("%d\n", htab_hash_function("bob") % array_size);
    printf("%d\n", htab_hash_function("tom") % array_size);
    printf("%d\n", htab_hash_function("steve") % array_size);
    printf("%d\n", htab_hash_function("rose") % array_size);
    printf("%d\n", htab_hash_function("jerry") % array_size);
    printf("%d\n", htab_hash_function("alphons") % array_size);
    printf("%d\n", htab_hash_function("kate") % array_size);
    printf("%d\n", htab_hash_function("jimmy") % array_size);
    printf("%d\n", htab_hash_function("peter") % array_size);
    return 0;
}