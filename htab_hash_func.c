/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_hash_func.c hash function
 * @date 19.4.2022
 */

#include <stdint.h>
#include "htab_private.h"

size_t htab_hash_function(htab_key_t str) {
    uint32_t hash = 0;
    unsigned char* p;

    for (p = (unsigned char*)str; *p != '\0'; p++) {
        hash = 65599 * hash + *p;
    }
    return hash;
}
