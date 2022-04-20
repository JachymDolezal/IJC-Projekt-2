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

/*
    word word2
*/

/*
Napište funkci

        int read_word(char *s, int max, FILE *f);

      která čte jedno slovo ze souboru f do zadaného pole znaků
      a vrátí délku slova (z delších slov načte prvních max-1 znaků,
      a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
      Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
      Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.

    Omezení: řešení v C bude tisknout jinak uspořádaný výstup
      a je povoleno použít implementační limit na maximální
      délku slova (např. 127 znaků), delší slova se ZKRÁTÍ a program
      při prvním delším slovu vytiskne varování na stderr (max 1 varování).

    Poznámka: Vhodný soubor pro testování je například seznam slov
              v souboru /usr/share/dict/words
              nebo texty z http://www.gutenberg.org/
              případně výsledek příkazu:  "seq 1000000 2000000|shuf"

*/