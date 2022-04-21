/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_clear.c clears the hash table
 * @date 19.4.2022
 */

#include <stdlib.h>
#include "htab_private.h"

void htab_clear(htab_t* t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr_ptr[i] != NULL) {
            htab_item_t* pair = t->arr_ptr[i];
            while (pair != NULL) {
                htab_item_t* tmp = pair->next;
                free((char*)pair->pair.key);
                free(pair);
                pair = tmp;
            }
            t->arr_ptr[i] = NULL;
        }
    }
}