run: main.o node.o user.o cpu.o
	gcc -pthread main.o node.o user.o cpu.o -o run
main.o: main.c
	gcc -c main.c
node.o: node.c node.h
	gcc -c node.c
user.o: user.c user.h
	gcc -c user.c
cpu.o: cpu.c cpu.h
	gcc -c cpu.c
clean:
	rm *.o run
