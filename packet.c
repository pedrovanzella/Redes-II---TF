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

#include "packet.h"
#include "usuario.h"

#define RCVBUFSIZE 3000
#define MAXPENDING 5  

void DieWithError(char *errorMessage)
{
  printf("Erro: %s\n", errorMessage);
  exit(1); // The Die part
}

void pacote_pretty_print(Packet* pkt)
{
  printf("\n\e[1m\e[32mpacote_pretty_print(): enviando\e[0m\n");
  printf("\tOperacao: %d\n", pkt->operacao);
  printf("\tIP: %s\n", pkt->IP);

  printf("\tUsuario:\n");
  printf("\t\tNome:\t%s\n", pkt->usr.nome);
  printf("\t\tSenha:\t%s\n", pkt->usr.senha);

  printf("\tAviao:\n");
  printf("\t\tNome:\t%s\n", pkt->voo.nome);
  printf("\t\tPartida:\t%4d\n", pkt->voo.partida);
  printf("\t\tChegada:\t%4d\n", pkt->voo.chegada);
  printf("\t\tStatus:\t%s\n", pkt->voo.status);

  printf("\t\tAssentos alocados:\n");
  int i;
  for(i = 0; i <= 150; i++)
  {
    if(pkt->voo.assentos[i][0] != '\0')
    {
      printf("\t\t\t[%3d] %s\n", i, pkt->voo.assentos[i]);
    }
  }
  printf("\n");
}

void HandleTCPClient(int clntSocket)
{
  char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
  int recvMsgSize,i=0;                    /* Size of received message */
  Packet *pkt;

  /* Receive message from client */
  if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
  {
    DieWithError("recv() failed");
  }
  /* echoBuffer retornado do cliente */

  /* Trata buffer */


  /* Altera buffer */

  /* Send received string and receive again until end of transmission */
  while (recvMsgSize > 0)      /* zero indicates end of transmission */
  {
    /* Echo message back to client */
    if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
    {
      DieWithError("send() failed");
    }

    /* See if there is more data to receive */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    {
      DieWithError("recv() failed");
    }
  }	
  close(clntSocket);    /* Close client socket */
}

char *envia_cliente_server(Packet *pkt)
{
  int sock;                        /* Socket descriptor */
  struct sockaddr_in echoServAddr; /* Echo server address */
  unsigned short echoServPort;     /* Echo server port */
  char *servIP;                    /* Server IP address (dotted quad) */
  char *echoString;                /* String to send to echo server */
  char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
  unsigned int echoStringLen;      /* Length of string to echo */
  int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() and total bytes read */

  servIP = pkt -> IP;             /* First arg: server IP address (dotted quad) */
  //echoString = pkt;         /* Second arg: string to echo */

  echoServPort = 2543;  /* 2543 eh uma porta alta, nao precisamos de root */

  /* Create a reliable, stream socket using TCP */
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  {
    DieWithError("socket() failed");
  }

  /* Construct the server address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
  echoServAddr.sin_family      = AF_INET;             /* Internet address family */
  echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
  echoServAddr.sin_port        = htons(echoServPort); /* Server port */

  /* Establish the connection to the echo server */
  if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
  {
    DieWithError("connect() failed");
  }

  echoStringLen = strlen(echoString);          /* Determine input length */

  /* Send the string to the server */
  if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
  {
    DieWithError("send() sent a different number of bytes than expected");
  }

  /* Receive the same string back from the server */
  totalBytesRcvd = 0;
  printf("Received: ");                /* Setup to print the echoed string */
  while (totalBytesRcvd < echoStringLen)
  {
    /* Receive up to the buffer size (minus 1 to leave space for
       a null terminator) bytes from the sender */
    if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
    {
      DieWithError("recv() failed or connection closed prematurely");
    }
    totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
    echoBuffer[bytesRcvd] = '\0';  /* Terminate the string! */

    printf("%s", echoBuffer);      /* Print the echo buffer */
  }

  printf("\n");    /* Print a final linefeed */

  close(sock);
  //	return *echoBuffer;
}

void servidor()
{
  int servSock;                    /* Socket descriptor for server */
  int clntSock;                    /* Socket descriptor for client */
  struct sockaddr_in echoServAddr; /* Local address */
  struct sockaddr_in echoClntAddr; /* Client address */
  unsigned short echoServPort;     /* Server port */
  unsigned int clntLen;            /* Length of client address data structure */

  echoServPort = 2543;  /* Porta local, 2543 eh porta alta */

  /* Create socket for incoming connections */
  if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  {
    DieWithError("socket() failed");
  }

  /* Construct local address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
  echoServAddr.sin_family = AF_INET;                /* Internet address family */
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
  echoServAddr.sin_port = htons(echoServPort);      /* Local port */

  /* Bind to the local address */
  if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
  {
    DieWithError("bind() failed");
  }

  /* Mark the socket so it will listen for incoming connections */
  if (listen(servSock, MAXPENDING) < 0)
  {
    DieWithError("listen() failed");
  }

  for (;;) /* Run forever */
  {
    /* Set the size of the in-out parameter */
    clntLen = sizeof(echoClntAddr);

    /* Wait for a client to connect */
    if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
    {
      DieWithError("accept() failed");
    }

    /* clntSock is connected to a client! */

    //printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

    HandleTCPClient(clntSock);
  }
  /* NOT REACHED */
}
