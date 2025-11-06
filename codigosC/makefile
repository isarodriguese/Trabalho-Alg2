# Makefile de exemplo (Manual do GNU Make)
CFLAGS = -Wall -Werror -Wextra -std=c99 -g # flags de compilacao
LDFLAGS = -Lm

CC = gcc

# arquivos-objeto
	objects = main.o functions.o

main: main.o functions.o
	$(CC) -o main main.o functions.o $(LDFLAGS)

functions.o: functions.c
	$(CC) -c $(CFLAGS) functions.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main