ifeq ($(ver), release)
	RELEASE_FLAG = -D RELEASE
endif

CC = gcc
CFLAGS += -g -std=gnu99 -Wall
LIB = -lpthread -L./
# INCLUDE = -I /usr/src/linux-headers-3.13.0-32/include


#OBJ_FILES = ./send_ARM_firmware.o ./util/invglog.o ./net_process.o ./globle.h ./crc16.o
C_FILES = $(shell ls *.c)
#C_FILES += $(shell ls ./util/*.c)
OBJ_FILES = $(patsubst %.c, %.o, $(C_FILES))

NAME = a.out 

all:$(NAME)

$(NAME):$(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -lpthread  -o $@ $(LIB) $(RELEASE_FLAG)
	
clean:
	rm $(NAME) *.o
	find ./ -name "*~" -or -name "*~" | xargs rm -rf

# check_s:
# 	valgrind ./server
# check_c:
# 	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --num-callers=20 ./client

release:
	@make all ver=release


# .c.o:
# 	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $<
%.o:%.c
	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(LIB) $< $(RELEASE_FLAG)
	@echo "------------------"
