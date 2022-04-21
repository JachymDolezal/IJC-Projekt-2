/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_resize.c
 * @date 19.4.2022
 */

#include <stdlib.h>
#include "htab_private.h"

void htab_resize(htab_t* t, size_t newm) {
    size_t old_size = t->arr_size;
    t->arr_size = newm;
    htab_item_t** old_arr_ptr = t->arr_ptr;
    t->arr_ptr = calloc(newm, sizeof(htab_item_t*));

    for (size_t i = 0; i < old_size; i++) {
        if (old_arr_ptr[i] == NULL) {
            continue;
        } else {
            htab_item_t* tmp = old_arr_ptr[i];
            while (tmp != NULL) {
                htab_item_t* tmp2 = tmp->next;
                htab_lookup_add(t, tmp->pair.key);
                free((char*)tmp->pair.key);
                free(tmp);
                t->size--;
                tmp = tmp2;
            }
            old_arr_ptr[i] = NULL;
        }
    }
    free(old_arr_ptr);
}