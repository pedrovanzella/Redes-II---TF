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
    if(pkt->voo.assentos[i] != 0)
    {
      printf("\t\t\t[%3d] %d\n", i, pkt->voo.assentos[i]);
    }
  }
  printf("\n");
}

void Cliente()
{

}

void Servidor()
{

}
