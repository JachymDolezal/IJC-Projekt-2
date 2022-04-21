/*
 * @name Jáchym Doležal, xdolez0c
 * @faculty VUT FIT 2021/2022
 * @brief tail.c POSIX tail
 * @date 19.4.2022
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

#define LIMIT 4095

#define DEFAULT_N 20

int main(int argc, char* argv[]) {
    // param check
    bool warn = false;
    bool error = false;
    if (argc > 4) {
        error_exit(
            "Chyba: nepovolený počet argumentů.\nPoužití: %s[-n][cislo][file] ",
            argv[0]);
    }

    long n = 10;
    char* arg_check;
    FILE* file;
    int file_name = 0;

    switch (argc) {
        case 1:
            break;
        case 2:
            file_name = 1;
            break;
        case 3:
            if (argv[1][0] == '-') {
                if (argv[1][1] == 'n') {
                    n = strtol(argv[2], &arg_check, 10);
                    if (strlen(arg_check) > 0) {
                        error = true;
                        break;
                    }
                } else {
                    error = true;
                    break;
                }
            } else {
                error = true;
                break;
            }
            break;
        case 4:
            if (argv[1][0] == '-') {
                if (argv[1][1] == 'n') {
                    n = strtol(argv[2], &arg_check, 10);
                    if (strlen(arg_check) > 0) {
                        error = true;
                        break;
                    }
                } else {
                    error = true;
                    break;
                }
                file_name = 3;
            } else {
                file_name = 1;
                if (argv[2][0] == '-') {
                    if (argv[2][1] == 'n') {
                        n = strtol(argv[3], &arg_check, 10);
                        if (strlen(arg_check) > 0) {
                            error = true;
                            break;
                        }
                    } else {
                        error = true;
                        break;
                    }
                } else {
                    error = true;
                    break;
                }
                break;
            }
            break;
        default:
            break;
    }

    if (error == true) {
        error_exit(
            "Chyba: nepovolený vstupní parametr\nPoužití: %s "
            "[-n][cislo][file]",
            argv[0]);
    }

    // todo check ze nacitany radek je mensi nez implementacni limit.
    //  printf("n: %d\n file: %s\n", n, argv[file_name]);

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
    while ((fgets(buffer[idx], LIMIT + 1, file)) != NULL) {
        if (buffer[idx][LIMIT - 1] != '\n' && strlen(buffer[idx]) == LIMIT) {
            buffer[idx][LIMIT] = '\n';
            buffer[idx][LIMIT + 1] = '\0';

            if (warn == false) {
                warning_msg("Chyba: překročen implementační limit řádku.");
                warn = true;
            }
            while (fgetc(file) != '\n') {
            }
            //
        }

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