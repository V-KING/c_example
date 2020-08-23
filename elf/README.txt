# elf二进制文件中写入自定义信息

## 在elf中写入版本信息
在elf中写入可识别的版本信息有两种方式
1. 使用objcopy. (see Makefile.main)
2. 使用-Wl,--defsym,VERISON_1_0=0. (see Makefile.test)
3. 添加section
```shell
$ echo 'int main() { puts ("Hello world"); }' | gcc -x c - -c -o hello.o

$ echo "this is my special data" >version

$ objcopy --add-section .version=version --set-section-flags .version=noload,readonly hello.o hello2.o

$ gcc hello2.o -o hello

$ ./hello
Hello world

$ objdump -sj .version hello
```

在ubuntu的32位系统撒花姑娘上测试通过，证明可用。
在二进制文件中有相应的版本信息的字符串.


```Makefile
BUILD = $(shell date +"%Y%m%d_%H%M%S")
VERSION=VERSION_v1.0
LDLIBS = -Wl,--defsym,$(VERSION)_$(BUILD)=0

all:main test

main: main.o version.o
    gcc $(LDLIBS) $^ -o main

main.o : main.c 
    gcc $(LDLIBS) -c main.c -o main.o
version.o:version
    objcopy -I binary -O elf32-i386 -B i386 version version.o
#objcopy -I binary -O elf3-littlearm -B arm version version.o
    
# objdump -i
# objdump -t version.o
# readelf -a version.o
# hexdump -C test

test: test.o
    gcc $(LDLIBS) test.o -o test
test.o: test.c
    gcc $(LDLIBS) -c test.c  -o test.o

clean:
    rm *.o main test
```
