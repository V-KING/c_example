ifeq ($(ver), release)
	RELEASE_FLAG = -D RELEASE
endif

CC = gcc
CFLAGS += -g -std=gnu99 -Wall -Woverride-init -Wsign-compare -Wtype-limits -Wuninitialized
LIB = -lpthread -L./
# INCLUDE = -I /usr/src/linux-headers-3.13.0-32/include


OBJ_FILES = ./crc16_calculate.o
NAME = crc16_calculate 

all:$(NAME)

$(NAME):$(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -lpthread  -o $@ $(LIB) $(RELEASE_FLAG)
	
clean:
	rm $(NAME) *.o
	find ./ -name "*~" | xargs rm

# check_s:
# 	valgrind ./server
# check_c:
# 	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --num-callers=20 ./client

release:
	# Release a Version
	@make all ver=release
test:
	@make clean
	@make all


# .c.o:
# 	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(IFLAGS) $<
%.o:%.c
	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(IFLAGS) $(LIB) $< $(RELEASE_FLAG)
	@echo "------------------"
