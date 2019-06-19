
target=main
CC=gcc

# !!!
INCLUDE = -I../include
LDFLAGS = 

CFLAGS = -std=gnu9x -g $(INCLUDE) -w

Q=@
NQ=echo
# Q=
# NQ=true

all:main

$(target):main.o
	@$(NQ) executable file:  $(target)
	$(Q)$(CC) $(CFLAGS) $^ -o $(target) $(LDFLAGS)

%.o: %.c
	@$(NQ) generate:   $@
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(target) *~ *.o