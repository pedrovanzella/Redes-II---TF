all: trafficcontrol

trafficcontrol: main.o usuario.o aviao.o packet.o
	gcc -Wall -o trafficcontrol main.o usuario.o aviao.o packet.o

servidor: main.c usuario.c aviao.c packet.c
	gcc -Wall -o servidor main.c usuario.c aviao.c packet.c

main.o: main.c
	gcc -Wall -c main.c

usuario.o: usuario.c usuario.h
	gcc -Wall -c usuario.c

aviao.o: aviao.c aviao.h
	gcc -Wall -c aviao.c

packet.o : packet.c packet.h
	gcc -Wall -c packet.c
	
clean:
	rm -rf *.o trafficcontrol servidor
