/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief htab_lookup_add.c finds pair in hashtable and if not found it adds the
 * element to the hash table.
 * @date 19.4.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "htab_private.h"
#define AVG_LEN_MAX 1.5
/*
chose this value based on testing results.
*/

htab_item_t* create_new_pair(htab_key_t key) {
    htab_item_t* new_pair = malloc(sizeof(htab_item_t));
    if (new_pair == NULL) {
        return NULL;
    }

    size_t str_size = strlen(key) + 1;
    new_pair->pair.key = malloc(str_size);
    if (new_pair->pair.key == NULL) {
        free(new_pair);
        return NULL;
    }
    memcpy((char*)new_pair->pair.key, key, str_size);
    new_pair->next = NULL;
    new_pair->pair.value = 0;

    return new_pair;
}

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {
    if (t->size > t->arr_size * AVG_LEN_MAX) {
        htab_resize(t, (t->arr_size * 2));
    }
    size_t index = (htab_hash_function(key) % t->arr_size);
    htab_item_t* tmp = t->arr_ptr[index];
    htab_pair_t* p = htab_find(t, key);
    if (p != NULL) {
        return p;
    }

    htab_item_t* new_pair = create_new_pair(key);
    if (new_pair == NULL) {
        return NULL;
    }
    t->size++;

    if (t->arr_ptr[index] == NULL) {
        t->arr_ptr[index] = new_pair;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_pair;
    }
    return &(new_pair->pair);
}