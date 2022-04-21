/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_size.c returns number of elements in hashtable.
 * @date 19.4.2022
 */

#include "htab_private.h"

size_t htab_size(const htab_t* t) {
    return t->size;
}