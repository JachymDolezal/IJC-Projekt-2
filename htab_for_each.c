/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_for_each.c does a function upon all pairs in hash table
 * @date 19.4.2022
 */

#include <stdlib.h>
#include "htab_private.h"

void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t* tmp = t->arr_ptr[i];
        while (tmp != NULL) {
            (*f)(&tmp->pair);
            tmp = tmp->next;
        }
    }
}