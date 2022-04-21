/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_erase.c deletes given pair
 * @date 19.4.2022
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "htab_private.h"
#define AVG_LEN_MIN 0.35
/*
chose this value as most optimal from doing numerous tests.
*/

bool htab_erase(htab_t* t, htab_key_t key) {
    if (t->size < t->arr_size * AVG_LEN_MIN) {
        htab_resize(t, (t->arr_size / 2));
    }
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t* tmp = t->arr_ptr[index];

    if (tmp == NULL) {
        return false;
    }

    if (!strcmp(tmp->pair.key, key)) {
        if (tmp->next == NULL) {
            free((char*)tmp->pair.key);
            free(tmp);
            t->arr_ptr[index] = NULL;
        } else {
            htab_item_t* tmp_next = tmp->next;
            free((char*)tmp->pair.key);
            free(tmp);
            t->arr_ptr[index] = tmp_next;
        }
        t->size--;
        return true;
    }

    while (tmp->next != NULL) {
        if (!strcmp(tmp->next->pair.key, key)) {
            htab_item_t* tmp_next = tmp->next->next;
            free((char*)tmp->next->pair.key);
            free(tmp->next);
            tmp->next = tmp_next;
        }
        if (tmp->next != NULL) {
            tmp = tmp->next;
        } else {
            continue;
        }
    }
    t->size--;
    return true;
}