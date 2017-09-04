ifeq ($(test), testmain)
	RELEASE_FLAG = -D testmain
endif

CC = gcc
CFLAGS += -g -std=gnu99 -Wall -Woverride-init -Wsign-compare -Wtype-limits -Wuninitialized
LIB = -lpthread -L./
# INCLUDE = -I /usr/src/linux-headers-3.13.0-32/include



all:./getPidByName.o

a.out: ./getPidByName.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIB) $(RELEASE_FLAG)
	
clean:
	rm a.out *.o
rmobj:
	ifeq ("getPidByName.o", $(wildcard "*.o"))
	rm *.o
	endif
main:
	@make a.out test=testmain


# .c.o:
# 	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(IFLAGS) $<
%.o:%.c
	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(IFLAGS) $(LIB) $< $(RELEASE_FLAG)
	@echo "------------------"
