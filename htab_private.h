/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_private.h private .h file (not available to the user)
 * @date 19.4.2022
 */

#include "htab.h"

typedef struct htab_item htab_item_t;

struct htab_item {
    htab_pair_t pair;
    htab_item_t* next;
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item** arr_ptr;
};
