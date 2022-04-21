/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief 2. příklad - knihovna
 * @date 19.4.2022
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "htab_private.h"

#define VZK_SIZE 9

int main() {
    htab_t* h = htab_init(5);
    if (h == NULL) {
        error_exit("chyba pri alokaci");
    }
    printf("htab number of elements: %ld\n", htab_size(h));
    printf("htab array size: %ld\n", htab_bucket_count(h));

    char* vzk[VZK_SIZE] = {"michal",  "oliver", "martinS", "martinA", "albert",
                           "krystof", "tonda",  "dan",     "vojta"};

    for (int i = 0; i < VZK_SIZE; i++) {
        printf("index : %ld, name : %s \n",
               htab_hash_function(vzk[i]) % VZK_SIZE, vzk[i]);
        htab_pair_t* p = htab_lookup_add(h, vzk[i]);
        printf("added %s with data: %d\n", p->key, p->value);
    }

    // for (size_t i = 0; i < h->arr_size; i++) {
    //     if (h->arr_ptr[i] == NULL) {
    //         printf("-|\n");
    //     } else {
    //         printf("->");
    //         htab_item_t* tmp = h->arr_ptr[i];
    //         while (tmp != NULL) {
    //             printf(" %s -> ", tmp->pair.key);
    //             tmp = tmp->next;
    //         }
    //         printf("NULL \n");
    //     }
    // }
    printf("removed %s sucess: %d\n", vzk[1], htab_erase(h, "oliver"));
    printf("removed %s sucess: %d\n", "krystof", htab_erase(h, "krystof"));
    printf("removed %s sucess: %d\n", "vojta", htab_erase(h, "vojta"));

    // for (size_t i = 0; i < h->arr_size; i++) {
    //     if (h->arr_ptr[i] == NULL) {
    //         printf("-|\n");
    //     } else {
    //         printf("->");
    //         htab_item_t* tmp = h->arr_ptr[i];
    //         while (tmp != NULL) {
    //             printf(" %s -> ", tmp->pair.key);
    //             tmp = tmp->next;
    //         }
    //         printf("NULL \n");
    //     }
    // }
    printf("arr size: %d\n", h->arr_size);
    // printf("htab number of elements: %ld\n", htab_size(h));
    // for (int i = 0; i < VZK_SIZE; i++) {
    //     htab_pair_t* f = htab_find(h, vzk[i]);
    //     if (f != NULL) {
    //         printf("found %s\n", f->key);
    //     }
    // }
    // printf("added %s sucess: %d\n", vzk[1], htab_lookup_add(h, "oliver"));
    // printf("added %s sucess: %d\n", "krystof", htab_lookup_add(h,
    // "krystof")); printf("added %s sucess: %d\n", "vojta", htab_lookup_add(h,
    // "vojta"));
    printf("-----------------\n");
    // for (size_t i = 0; i < h->arr_size; i++) {
    //     if (h->arr_ptr[i] == NULL) {
    //         printf("-|\n");
    //     } else {
    //         printf("->");
    //         htab_item_t* tmp = h->arr_ptr[i];
    //         while (tmp != NULL) {
    //             printf(" %s -> ", tmp->pair.key);
    //             tmp = tmp->next;
    //         }
    //         printf("NULL \n");
    //     }
    // }
    printf("-----------------\n");
    printf("arr size: %d\n", h->arr_size);
    printf("number of elements: %d\n", h->size);
    htab_free(h);

    return 0;
}