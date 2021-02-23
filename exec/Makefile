ifeq ($(ver), release)
	RELEASE_FLAG = -D RELEASE
endif

CC = gcc
CFLAGS += -g -std=gnu99 -Wall -Woverride-init -Wsign-compare -Wtype-limits -Wuninitialized
LIB = -lpthread -L./
# INCLUDE = -I /usr/src/linux-headers-3.13.0-32/include



all:task_ls task_control getPidByName

task_ls:./task_ls.o
	$(CC) $(CFLAGS) $^ -lpthread  -o $@ $(LIB) $(RELEASE_FLAG)

task_control:./task_control.o ./test/getPidByName.o
	$(CC) $(CFLAGS) $^ -lpthread  -o $@ $(LIB) $(RELEASE_FLAG)

getPidByName:
	@make -C test

clean:
	@make -C test clean
	rm task_ls task_control *.o
	find ./ -name "*~" -or -name "*~" | xargs rm -rf

release:
	@make all ver=release


# .c.o:
# 	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(IFLAGS) $<
%.o:%.c
	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(IFLAGS) $(LIB) $< $(RELEASE_FLAG)
	@echo "------------------"
