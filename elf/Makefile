
BUILD = $(shell date +"%Y%m%d_%H%M%S")
VERSION=VERSION_v1.0
LDLIBS = -Wl,--defsym,$(VERSION)_$(BUILD)=0

all:a.out test

a.out: main.o version.o
	gcc $(LDLIBS) $^ -o main

main.o : main.c 
	gcc $(LDLIBS) -c main.c -o main.o
version.o:version
	objcopy -I binary -O elf32-i386 -B i386 version version.o
#arm-linux-objcopy -I binary -O elf32-littlearm -B arm version version.o
	
# objdump -i
# objdump -t version.o
# readelf -a version.o
# hexdump -C test



test: test.o
	gcc $(LDLIBS) test.o -o test
test.o: test.c
	gcc $(LDLIBS) -c test.c  -o test.o

clean:
	rm *.o main test *~