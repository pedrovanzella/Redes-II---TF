all: trafficcontrol

trafficcontrol: main.o usuario.o aviao.o packet.o
	gcc -o trafficcontrol main.o usuario.o aviao.o packet.o

servidor: main.c usuario.c aviao.c packet.c
	gcc -o servidor main.c usuario.c aviao.c packet.c

main.o: main.c
	gcc -c main.c

usuario.o: usuario.c usuario.h
	gcc -c usuario.c

aviao.o: aviao.c aviao.h
	gcc -c aviao.c

packet.o : packet.c packet.h
	gcc -c packet.c
	
clean:
	rm -rf *.o trafficcontrol servidor
