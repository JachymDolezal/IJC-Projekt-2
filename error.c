/*
 * error.c
 * IJC-DU1, příklad b), 18.3.2022
 * Autor: Jáchym Doležal, FIT
 * Login: xdolez0c
 * Přeloženo: gcc 10.2.1 (Debian 10.2.1-6)
 */

#include <error.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning_msg(const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}
void error_exit(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}