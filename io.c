/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief io.c reads one word in a file and returns its length
 * @date 19.4.2022
 */

#include "io.h"
#include <ctype.h>
#include "error.h"
#include "stdbool.h"
#include "stdio.h"

int read_word(char* s, int max, FILE* f) {
    int c = 0;
    int length = 0;
    bool limit = false;

    if (f == NULL) {
        warning_msg("Chyba: neexistujici soubor");
        return -2;
    }

    while (((c = fgetc(f)) != EOF) && isspace(c)) {
    }

    if (c == EOF) {
        return EOF;
    }

    s[length++] = c;

    while (((c = fgetc(f)) != EOF) && !isspace(c)) {
        if (length == max - 1) {
            limit = true;
            break;
        }
        s[length] = c;
        length++;
    }

    s[length] = '\0';

    if (limit) {
        while (((c = fgetc(f)) != EOF) && !isspace(c)) {
        }
        return 0;
    }

    return length;
}