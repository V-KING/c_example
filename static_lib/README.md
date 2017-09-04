
# 静态库
## 1. 生成.a文件
```
gcc –c test.c
ar cr libtest.a test.o
```
## 2. 使用.a文件生成可执行文件
放在/lib和/usr/lib和/usr/local/lib里的库直接用-l参数就能链接了，
但如果库文件没放在这三个目录里，而是放在其他目录里，这时我们
只用-l参数的话，链接还是会出错，出错信息大概是：
“/usr/bin/ld: cannot find -lxxx”，也就是链接程序ld在那3个目录里
找不到libxxx.so，这时另外一个参数-L就派上用场了，
比如常用的X11的库，它在/usr/X11R6/lib目录下，我们编译时就要
用-L/usr/X11R6/lib -lX11参数，-L参数跟着的是库文件所在的目录名。
再比如我们把libtest.so放在/aaa/bbb/ccc目录下，那链接参数就
是-L/aaa/bbb/ccc -ltest
```
gcc -c main.c
gcc -o app main.o -L. -ltest
```
