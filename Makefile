all: main

main: main.o conn.o
	gcc -g -o $@ $^ 

%.o: %.c
	gcc -g -c $^


clean:
	rm -f main
	rm -f *.o

