/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_find.c finds given pair in hash table
 * @date 19.4.2022
 */

#include <stdlib.h>
#include <string.h>
#include "htab_private.h"

htab_pair_t* htab_find(htab_t* t, const htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t* tmp = t->arr_ptr[index];

    if (tmp == NULL) {
        return NULL;
    }

    while (tmp != NULL) {
        if (!strcmp(tmp->pair.key, key)) {
            return &(tmp->pair);
        }
        tmp = tmp->next;
    }

    return NULL;
}