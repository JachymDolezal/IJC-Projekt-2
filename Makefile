 # Makefile
 # IJC-DU2, 5.4.2022
 # Autor: Jáchym Doležal, FIT
 # Login: xdolez0c
 # Popis: Makefile pomoci příkazu: "make" vytvoří všechny spustitelné soubory,

CC = gcc
CPPFLAGS = -g -std=c++17 -pedantic -Wall -Wextra 
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra 

EXEC = tail wordcount wordcount-dynamic
OBJ = error.o tail.o

all: tail wordcount wordcount-dynamic

tail: tail.o error.o 
	$(CC) $(CFLAGS) $(OBJ) -o tail

wordcount: htab_lib error.o wordcount_c.o io.o
	$(CC) $(CFLAGS) error.o wordcount_c.o io.o -o wordcount htablib.a

wordcount-dynamic: error.o htab_dynamic wordcount_c.o io.o
	$(CC) $(CFLAGS) error.o wordcount_c.o io.o -o wordcount-dynamic htablib.so

htab_lib: htab_static
	ar rsv htablib.a htab_*.o

htab_static: error.o htab.h
	$(CC) $(CFLAGS) -c htab_*.c

htab_dynamic: htab.h htab_private.h
	gcc -shared -o htablib.so -fpic htab_*.c

io.o: error.o
	$(CC) $(CFLAGS) -c io.c -o io.o

wordcount_c.o: htab.h wordcount.c
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount_c.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

tail.o: tail.c error.o
	$(CC) $(CFLAGS) -c tail.c -o tail.o

#util

clean: 
	rm $(EXEC) *.o *.out *.zip

zip:
	zip xdolez0c.zip *.c *.h Makefile
