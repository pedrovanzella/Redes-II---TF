/*******************************************
 * socket.c                                *
 * Catinae, Matheus da Rosa, Pedro Vanzella*
 *                                         *
 * Redes 2                                 *
 *******************************************/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "packet.h"
#include "usuario.h"
#include "aviao.h"

void pacote_pretty_print(Packet* pkt)
{
  struct usuario* usr;
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
    if(pkt->voo.assentos[i] != 0)
    {
      usr = find_by_id(pkt->voo.assentos[i]);
      printf("\t\t\t[%3d] [%d] %s\n", i, pkt->voo.assentos[i], usr->nome);
    }
  }
  printf("\n");
}

void Cliente()
{
  int sock, bytes_recieved;  
  char buffer[1024];
  struct hostent *host;
  struct sockaddr_in server_addr;  
  char serverIP[20];
  char op;
  int ass;
  int usr_id = 0;
  
  Packet* pkt;
  pkt = (Packet*)malloc(sizeof(Packet));
  memset(pkt, '\0', sizeof(Packet));

  printf("IP do servidor> ");
  scanf("%s", serverIP);

  host = gethostbyname(serverIP);

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Socket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;     
  server_addr.sin_port = htons(5000);   
  server_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(server_addr.sin_zero),8); 

  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) 
  {
    perror("Connect");
    exit(1);
  }

  while(1)
  {
    /*********** RECEBE DO SERVER **************/
    bytes_recieved = recv(sock, buffer, 1024, 0);

    pkt = (Packet*)buffer;

    switch(pkt->operacao)
    {
      case 0: // HELLO
        printf("HELLO>\n> ");
        break;
      case 2: // LOGIN FALHOU
        pkt->operacao = 1; // Pedido de login
        printf("LOGIN> ");
        scanf("%s", pkt->usr.nome);
        printf("SENHA> ");
        scanf("%s", pkt->usr.senha);
        send(sock, buffer, sizeof(buffer), 0); 
        break;
      case 4: // FALHA
        printf("FALHA>\n> ");
        break;
      case 3: // SUCESSO
        printf("SUCESSO>\n> ");
        break;
      case 7: // RESPOSTA DE CONSULTA
        printf("PARTIDA: %d\tCHEGADA: %d\nSTATUS: %s\n> ", pkt->voo.partida, pkt->voo.chegada, pkt->voo.status);
        break;
    }

    /***************** ENVIA PARA O SERVER ****************/
    memset(pkt, '\0', sizeof(Packet)); // Zerar meu pacote depois que li ele

    op = getchar();
    switch(op)
    {
      case 'l': // LOGIN
        pkt->operacao = 1; // Pedido de login
        printf("LOGIN> ");
        scanf("%s", pkt->usr.nome);
        printf("SENHA> ");
        scanf("%s", pkt->usr.senha);
        send(sock, buffer, sizeof(buffer), 0); 
        break;
      case 'r': // RESERVA ASSENTO
        pkt->operacao = 5; // Pedido de reserva
        printf("VOO> ");
        scanf("%s", pkt->voo.nome);
        printf("ASSENTO> ");
        scanf("%d", &ass);
        pkt->voo.assentos[ass] = usr_id;
        send(sock, buffer, sizeof(buffer), 0);
        break;
      case 'c': // CONSULTA VOO
        pkt->operacao = 6; // Pedido de consulta
        printf("VOO> ");
        scanf("%s", pkt->voo.nome);
        send(sock, buffer, sizeof(buffer), 0);
        break;
      default:
        printf("Operacao desconhecida!\n");
        continue;
    }
  }   
}

void Servidor()
{
  int sock, connected, bytes_recieved , true = 1;  
  char buffer[1024];

  Packet* pkt;
  pkt = (Packet*)malloc(sizeof(Packet));
  memset(pkt, '\0', sizeof(Packet));
  memset(buffer, '\0', sizeof(buffer));

  struct sockaddr_in server_addr,client_addr;    
  int sin_size;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Socket");
    exit(1);
  }

  if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) 
  {
    perror("Setsockopt");
    exit(1);
  }

  server_addr.sin_family = AF_INET;         
  server_addr.sin_port = htons(5000);     
  server_addr.sin_addr.s_addr = INADDR_ANY; 
  bzero(&(server_addr.sin_zero),8); 

  if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
  {
    perror("Unable to bind");
    exit(1);
  }

  if (listen(sock, 5) == -1) {
    perror("Listen");
    exit(1);
  }

  printf("\nTCPServer Waiting for client on port 5000");
  

  fflush(stdout);

  while(1)
  {  
    /* Envia HELLO */
    send(connected, buffer,strlen(buffer), 0); 

    sin_size = sizeof(struct sockaddr_in);

    connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

    printf("\nI got a connection from (%s , %d)", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    while (1)
    {
      /********************* RECEBE DO CLIENTE ******************/
      bytes_recieved = recv(connected,buffer,1024,0);

      pkt = (Packet *)buffer;

      switch(pkt->operacao)
      {
        case 1: // Pedido de Login
          if(login(pkt->usr.nome, pkt->usr.senha))
          {
            pkt->operacao = 3; // SUCESSO!
          }
          else
          {
            pkt->operacao = 2; // Falha de login
          }
          send(connected, buffer,strlen(buffer), 0);  
          break;
        case 5: // Pedido de reserva
          break;
        case 6: // Pedido de consulta
          break;
        default:
          break;
      }
    }
  }       

  close(sock);
}
