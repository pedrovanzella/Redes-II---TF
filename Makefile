all: trafficcontrol

trafficcontrol: main.o usuario.o aviao.o
	gcc -o trafficcontrol main.o usuario.o aviao.o

main.o: main.c
	gcc -c main.c

usuario.o: usuario.c usuario.h
	gcc -c usuario.c

aviao.o: aviao.c aviao.h
	gcc -c aviao.c

clean:
	rm -rf *.o trafficcontrol
