# Makefile de exemplo (Manual do GNU Make)
+
CFLAGS = -Wall -Werror -Wextra -std=99 -g # flags de compilacao
LDFLAGS = - Lm

CC = gcc

# arquivos-objeto
	objects = main.o heap.o

main: main.o heap.o
	$(CC) -o tp4 tp4.o heap.o $(LDFLAGS)

heap.o: heap.c
	$(CC) -c $(CFLAGS) heap.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main