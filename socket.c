/*******************************************
 * socket.c                                *
 * Catinae, Matheus da Rosa, Pedro Vanzella*
 *                                         *
 * Redes 2                                 *
 *******************************************/
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#include "socket.h"

#define ECHOMAX 255     /* Longest string to echo */

void DieWithError(char *errorMessage)
{
	/* TODO */
}

int envia_cliente_server(Packet* pkt)
{
  /* TODO */
  printf("envia_cliente_servidor(): enviando\n");
  printf("operacao: %d\n", pkt->operacao);
  printf("IP: %s\n", pkt->IP);
}

int Cliente(Packet *p)
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    struct sockaddr_in fromAddr;     /* Source address of echo */
    unsigned short echoServPort;     /* Echo server port */
    unsigned int fromSize;           /* In-out of address size for recvfrom() */
    char *servIP;                    /* IP address of server */
    char *echoString;                /* String to send to echo server */
    char echoBuffer[ECHOMAX+1];      /* Buffer for receiving echoed string */
    int echoStringLen;               /* Length of string to echo */
    int respStringLen;               /* Length of received response */
	
    servIP = p -> IP;           /* First arg: server IP address (dotted quad) */
    echoString = "Teste";       /* Second arg: string to echo */
	
    if ((echoStringLen = strlen(echoString)) > ECHOMAX)  /* Check input length */
        DieWithError("Echo word too long");
	
    /* if (argc == 4)
        echoServPort = atoi(argv[3]);  /* Use given port, if any *
    else */
	echoServPort = 7;  /* 7 is the well-known port for the echo service */
	
    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");
	
    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));    /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                 /* Internet addr family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);  /* Server IP address */
    echoServAddr.sin_port   = htons(echoServPort);     /* Server port */
	
    /* Send the string to the server */
    if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)
               &echoServAddr, sizeof(echoServAddr)) != echoStringLen)
        DieWithError("sendto() sent a different number of bytes than expected");
	
    /* Recv a response */
    fromSize = sizeof(fromAddr);
    if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, 
								  (struct sockaddr *) &fromAddr, &fromSize)) != echoStringLen)
        DieWithError("recvfrom() failed");
	
    if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        fprintf(stderr,"Error: received a packet from unknown source.\n");
        exit(1);
    }
	
    /* null-terminate the received data */
    echoBuffer[respStringLen] = '\0';
    printf("Received: %s\n", echoBuffer);    /* Print the echoed arg */
    
    close(sock);
    exit(0);
}

int Servidor()
{
    int sock;                        /* Socket */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned int cliAddrLen;         /* Length of incoming message */
    char echoBuffer[ECHOMAX];        /* Buffer for echo string */
    unsigned short echoServPort;     /* Server port */
    int recvMsgSize;                 /* Size of received message */
	
    echoServPort = 7;  /* First arg:  local port */
	
    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");
	
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */
	
    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");
	
    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        cliAddrLen = sizeof(echoClntAddr);
		
        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
									(struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
            DieWithError("recvfrom() failed");
		
        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
		
        /* Send received datagram back to the client */
        if (sendto(sock, echoBuffer, recvMsgSize, 0, 
				   (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize)
            DieWithError("sendto() sent a different number of bytes than expected");
    }
    /* NOT REACHED */
}
