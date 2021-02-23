# AR          = /home/fangy/arm-linux-gcc-3.4.1/usr/local/arm/3.4.1/bin/arm-linux-ar
# STRIP       = /home/fangy/arm-linux-gcc-3.4.1/usr/local/arm/3.4.1/bin/arm-linux-strip
#CC          = /home/fangy/arm-linux-gcc-3.4.1/usr/local/arm/3.4.1/bin/arm-linux-gcc
CC          = gcc -g

CFLAGS = -lpthread

all:client server tcp_client move

client: udp_client.o
	gcc $^ -o $@ $(CFLAGS)
udp_client.o:udp_client.c
	gcc  -c $< -o $@ $(CFLAGS)


server: udp_server.o
	$(CC)  $^ -o $@ $(CFLAGS)
udp_server.o:udp_server.c
	$(CC)  -c $< -o $@ $(CFLAGS)

tcp_client: tcp_client.o
	$(CC)  $^ -o $@ $(CFLAGS)
tcp_client.o:tcp_client.c
	$(CC)  -c $< -o $@ $(CFLAGS)

clean:
	rm client server *.o
move:
	cp ./server ./tcp_client /home/vk/nfs_share
	