CFLAGS = -Wall -Werror -Wextra -std=c99 -g

CC = gcc

	objects = main.o functions.o

main: main.o functions.o
	$(CC) -o main main.o functions.o $(LDFLAGS)

functions.o: functions.c
	$(CC) -c $(CFLAGS) functions.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main