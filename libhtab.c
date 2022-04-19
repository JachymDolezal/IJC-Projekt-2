#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "htab.h"

#define VZK_SIZE 9
// v libhtab
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

// v htab.h

size_t htab_hash_function(htab_key_t str) {
    uint32_t hash = 0;
    unsigned char* p;

    for (p = (unsigned char*)str; *p != '\0'; p++) {
        hash = 65599 * hash + *p;
    }
    return hash;
}

// Funkce pro práci s tabulkou:
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

size_t htab_size(const htab_t* t) {
    return t->size;
}
size_t htab_bucket_count(const htab_t* t) {
    return t->arr_size;
}

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

    /*
    todo
    vytvori novou tabulku

    -> vzit zaznam ze stare a pridat ho do nove (prehashovani)
    -> vzit data z value_stary -> value_novy
    */
}
// // (umožňuje rezervaci místa)

htab_pair_t* htab_find(htab_t* t, const htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t* tmp = t->arr_ptr[index];

    if (tmp == NULL) {
        return NULL;
    }

    while (tmp != NULL) {
        if (!strcmp(tmp->pair.key, key)) {
            return &(tmp->pair);
        }
        tmp = tmp->next;
    }

    return NULL;
}

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

bool htab_erase(htab_t* t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t* tmp = t->arr_ptr[index];

    if (tmp == NULL) {
        return false;
    }

    if (!strcmp(tmp->pair.key, key)) {
        if (tmp->next == NULL) {
            free((char*)tmp->pair.key);
            free(tmp);
            t->arr_ptr[index] = NULL;
        } else {
            htab_item_t* tmp_next = tmp->next;
            free((char*)tmp->pair.key);
            free(tmp);
            t->arr_ptr[index] = tmp_next;
        }
        t->size--;
        return true;
    }

    while (tmp->next != NULL) {
        if (!strcmp(tmp->next->pair.key, key)) {
            printf("tmp->next: %s\n", tmp->next->pair.key);

            htab_item_t* tmp_next = tmp->next->next;
            free((char*)tmp->next->pair.key);
            free(tmp->next);
            tmp->next = tmp_next;
        }
        if (tmp->next != NULL) {
            tmp = tmp->next;
        } else {
            continue;
        }
    }
    t->size--;
    return true;
}

// for_each: projde všechny záznamy a zavolá na ně funkci f
// Pozor: f nesmí měnit klíč .key ani přidávat/rušit položky
void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t* tmp = t->arr_ptr[i];
        while (tmp != NULL) {
            (*f)(&tmp->pair);
            tmp = tmp->next;
        }
    }
}

void htab_clear(htab_t* t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr_ptr[i] != NULL) {
            htab_item_t* pair = t->arr_ptr[i];
            while (pair != NULL) {
                htab_item_t* tmp = pair->next;
                free((char*)pair->pair.key);
                free(pair);
                pair = tmp;
            }
            t->arr_ptr[i] = NULL;
        }
    }
}
void htab_free(htab_t* t) {
    htab_clear(t);
    // debug for
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr_ptr[i] == NULL) {
            printf("-|\n");
        } else {
            printf("->");
            htab_item_t* tmp = t->arr_ptr[i];
            while (tmp != NULL) {
                printf(" %s -> ", tmp->pair.key);
                tmp = tmp->next;
            }
            printf("NULL \n");
        }
    }
    free(t->arr_ptr);
    free(t);
}

int main() {
    htab_t* h = htab_init(VZK_SIZE);
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

    for (size_t i = 0; i < h->arr_size; i++) {
        if (h->arr_ptr[i] == NULL) {
            printf("-|\n");
        } else {
            printf("->");
            htab_item_t* tmp = h->arr_ptr[i];
            while (tmp != NULL) {
                printf(" %s -> ", tmp->pair.key);
                tmp = tmp->next;
            }
            printf("NULL \n");
        }
    }
    printf("removed %s sucess: %d\n", vzk[1], htab_erase(h, "oliver"));
    printf("removed %s sucess: %d\n", "krystof", htab_erase(h, "krystof"));
    printf("removed %s sucess: %d\n", "vojta", htab_erase(h, "vojta"));

    for (size_t i = 0; i < h->arr_size; i++) {
        if (h->arr_ptr[i] == NULL) {
            printf("-|\n");
        } else {
            printf("->");
            htab_item_t* tmp = h->arr_ptr[i];
            while (tmp != NULL) {
                printf(" %s -> ", tmp->pair.key);
                tmp = tmp->next;
            }
            printf("NULL \n");
        }
    }

    printf("htab number of elements: %ld\n", htab_size(h));
    for (int i = 0; i < VZK_SIZE; i++) {
        htab_pair_t* f = htab_find(h, vzk[i]);
        if (f != NULL) {
            printf("found %s\n", f->key);
        }
    }
    htab_resize(h, 40);
    printf("added %s sucess: %d\n", vzk[1], htab_lookup_add(h, "oliver"));
    printf("added %s sucess: %d\n", "krystof", htab_lookup_add(h, "krystof"));
    printf("added %s sucess: %d\n", "vojta", htab_lookup_add(h, "vojta"));
    printf("-----------------\n");
    for (size_t i = 0; i < h->arr_size; i++) {
        if (h->arr_ptr[i] == NULL) {
            printf("-|\n");
        } else {
            printf("->");
            htab_item_t* tmp = h->arr_ptr[i];
            while (tmp != NULL) {
                printf(" %s -> ", tmp->pair.key);
                tmp = tmp->next;
            }
            printf("NULL \n");
        }
    }
    printf("-----------------\n");
    htab_free(h);

    return 0;
}