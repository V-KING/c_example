target=a.out

all:$(target)

a.out:main.o
	g++ $^ -o $@ -g

clean:
	rm *.o all
