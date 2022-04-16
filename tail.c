#include "tail.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

#define LIMIT 4095

#define DEFAULT_N 20

int main(int argc, char* argv[]) {
    // param check
    if (argc > 4) {
        error_exit("Chyba: nepovolený počet argumentů.");
    }

    long n = 10;
    char* arg_check;
    FILE* file;
    int file_name = 0;

    for (int i = 1; i < argc; i++) {
        // printf("argument: %d %s\n", i, argv[i]);
        if (argv[i][0] == '-' && argv[i][1] == 'n') {
            n = strtol(argv[i + 1], &arg_check, 10);
            if (strlen(arg_check) > 0) {
                error_exit("Chyba: nepovolený typ za přepínačem -n\n");
            }
            i++;
        } else {
            file_name = i;
        }
    }

    // todo check ze nacitany radek je mensi nez implementacni limit.
    //  printf("n: %d\n file: %s\n", n, argv[file_name]);

    // todo argument parsing
    // using get opt
    if (file_name == 0) {
        file = stdin;
    } else {
        file = fopen(argv[file_name], "r");
    }
    if (file == NULL) {
        error_exit("Chyba: chybný soubor.");
    }

    char** buffer = malloc(sizeof(char*) * n);
    if (buffer == NULL) {
        error_exit("Chyba: selhání při alokaci.");
    }

    for (int i = 0; i < n; i++) {
        buffer[i] = malloc(sizeof(char) * LIMIT);
        if (buffer[i] == NULL) {
            error_exit("Chyba: selhání při alokaci.");
        }
    }

    int idx = 0;
    bool rotate = false;
    while ((fgets(buffer[idx], LIMIT, file)) != NULL) {
        idx++;
        if (idx == n) {
            rotate = true;
            idx = 0;
        }
        if (rotate) {
            char* tmp_last = buffer[0];
            int i = 0;
            for (i = 0; i < n - 1; i++) {
                buffer[i] = buffer[i + 1];
            }
            buffer[n - 1] = tmp_last;
            idx = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s", buffer[i]);
        free(buffer[i]);
    }

    free(buffer);
    fclose(file);

    return 0;
}

/*

steps

parserovat inputs
    -2 options: ./tail soubor | ./tail -n int soubor
        else erorr


otevrit soubor
    -zkontrolovat

alokovat n radku do cyklyckeho bufferu (10 default)
    -kontrola mallocu
    -array of pointers na kazdy radek 4095 znaku dlouhy

projizdeni souboru fgets ukladani do bufferu cyklit kdyz jde pres limit

na konci projizdeni souboru vytisknout obsah bufferu na stdin


cyklicky buffer
---------------


-> radek 1
-> radek 2
-> radek 3
-> radek 4


radek 1 prepsat
shift array to left

-> radek 2
-> radek 3
-> radek 4
-> radek 5

*/