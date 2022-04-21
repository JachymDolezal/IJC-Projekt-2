/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_bucket_count.c returns array size
 * @date 19.4.2022
 */

#include "htab_private.h"

size_t htab_bucket_count(const htab_t* t) {
    return t->arr_size;
}