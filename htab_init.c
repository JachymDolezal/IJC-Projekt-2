/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_init.c initializes hash table
 * @date 19.4.2022
 */

#include <stdlib.h>
#include "error.h"
#include "htab_private.h"

htab_t* htab_init(size_t n) {
    if (n == 0) {
        error_exit("Chyba: tabulka musí obsahovat alespoň jeden řádek.");
    }
    htab_t* htab_new = malloc(sizeof(htab_t));
    if (htab_new == NULL) {
        return NULL;
    }
    htab_new->arr_ptr = malloc(sizeof(htab_item_t*) * n);
    if (htab_new->arr_ptr == NULL) {
        return NULL;
    }

    htab_new->size = 0;
    htab_new->arr_size = n;

    for (size_t i = 0; i < n; i++) {
        htab_new->arr_ptr[i] = NULL;
    }

    return htab_new;
}