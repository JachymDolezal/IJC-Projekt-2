/*
 * @licence žádná (Public domain)
 * @faculty VUT FIT 2021/2022
 * @brief htab.h -- rozhraní knihovny htab (řešení IJC-DU2)

 */

#ifndef __HTAB_H__
#define __HTAB_H__

#include <stdbool.h>
#include <string.h>

struct htab;
typedef struct htab htab_t;

typedef const char* htab_key_t;
typedef int htab_value_t;

typedef struct htab_pair {
    htab_key_t key;
    htab_value_t value;
} htab_pair_t;

size_t htab_hash_function(htab_key_t str);

htab_t* htab_init(size_t n);
size_t htab_size(const htab_t* t);
size_t htab_bucket_count(const htab_t* t);
void htab_resize(htab_t* t, size_t newn);

htab_pair_t* htab_find(htab_t* t, htab_key_t key);
htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key);

bool htab_erase(htab_t* t, htab_key_t key);

void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data));

void htab_clear(htab_t* t);
void htab_free(htab_t* t);

#endif