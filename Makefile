all: trafficcontrol

trafficcontrol: main.o usuario.o aviao.o socket.o
	gcc -o trafficcontrol main.o usuario.o aviao.o

main.o: main.c
	gcc -c main.c

usuario.o: usuario.c usuario.h
	gcc -c usuario.c

aviao.o: aviao.c aviao.h
	gcc -c aviao.c

socket.o : socket.c socket.h
	gcc -c socket.c
	
clean:
	rm -rf *.o trafficcontrol
