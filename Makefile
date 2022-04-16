 # Makefile
 # IJC-DU2, 5.4.2022
 # Autor: Jáchym Doležal, FIT
 # Login: xdolez0c
 # Popis: Makefile pomoci příkazu: "make" vytvoří všechny spustitelné soubory,
 # které se spouští pomocí příkazů: "make run" a "make steg".

CC = gcc
CPPFLAGS = -g -std=c++ -pedantic -Wall -Wextra -02
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2
MATH = -lm
EXEC = tail wordcount_c wordcount_cpp
OBJ = error.o tail.o
all: tail wordcount_c wordcount_cpp

#todo zjistit co je potreba 

#todo zjistit jak funguje linkovani knihoven

htab: libhtab.o error.o tail.o
	$(CC) $(CFLAGS) error.o libhtab.o -o htab $(MATH)

tail: tail.o error.o 
	$(CC) $(CFLAGS) $(OBJ) -o tail $(MATH)

wordcount_c: 
	$(CC) $(CFLAGS) $(INLINE) $(OBJ) -o wordcount_c$(MATH)

wordcount_cpp: 
	$(CC) $(CFLAGS) $(OBJ) -o wordcount_cpp $(MATH)

libhtab.o: libhtab.c htab.h
	$(CC) $(CFLAGS) -c libhtab.c -o libhtab.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

tail.o: tail.c error.o
	$(CC) $(CFLAGS) -c tail.c -o tail.o



#util

clean: 
	rm $(EXEC) *.o *.out *.zip

zip:
	zip xdolez0c.zip *.c *.h Makefile
