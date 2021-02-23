
target=client

CROSS_COMPILE?=

CFLAGS=-std=gnu9x -g

CC=$(CROSS_COMPILE)gcc

all:client server test

client:client.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

server:server.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
test:test.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm *.o client server *~

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
