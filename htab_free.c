/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_free.c frees memory of the hash tahble.
 * @date 19.4.2022
 */

#include <stdlib.h>
#include "htab_private.h"

void htab_free(htab_t* t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}