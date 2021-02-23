
target=main

CFLAGS=-std=gnu9x -g
CC=gcc

all:main

main:main.o crc16.o
	$(CC) $(CFLAGS) $^ -o $(target) $(LDFLAGS)

clean:
	rm *.o main *~

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
