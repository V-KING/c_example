ifeq ($(ver), release)
	RELEASE_FLAG = -D RELEASE
endif

CC = gcc
CFLAGS += -g -std=gnu99 -Wall -Woverride-init -Wsign-compare -Wtype-limits -Wuninitialized
LIB = -lpthread -L./ -lxml2
INCLUDE = -I /usr/include/libxml2
# INCLUDE = -I /usr/src/linux-headers-3.13.0-32/include


OBJ_FILES = ./createXMLfile.o
C_FILES = $(shell ls *.c)
# OBJ_FILES = ${patsubst %.c, %.o, $(C_FILES)}

NAME = createXMLfile

all:$(NAME) perseXMLdoc getAllNodeName

$(NAME):$(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -lpthread  -o $@ $(LIB) $(RELEASE_FLAG)

perseXMLdoc:perseXMLdoc.o
	$(CC) $(CFLAGS) $(INCLUDE) $^ -lpthread  -o $@ $(LIB) $(RELEASE_FLAG)
	
getAllNodeName:getAllNodeName.o
	$(CC) $(CFLAGS) $(INCLUDE) $^ -lpthread  -o $@ $(LIB) $(RELEASE_FLAG)
	
clean:
	rm $(NAME) *.o 
	find ./ -name "*~" -or -name "*~" | xargs rm -rf
	rm perseXMLdoc getAllNodeName

# check_s:
# 	valgrind ./server
# check_c:
# 	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --num-callers=20 ./client

release:
	# Release a Version
	@make all ver=release


# .c.o:
# 	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(IFLAGS) $<
%.o:%.c
	$(CC) -c -o $@ $(DEBUG) $(CFLAGS) $(INCLUDE) $(IFLAGS) $(LIB) $< $(RELEASE_FLAG)
	@echo "------------------"
