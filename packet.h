/*****************************************************
 * packet.h                                          *
 * Headers das funções do socket TCP                 *
 * Catiane, Matheus da Rosa, Pedro Vanzella          *
 *                                                   *
 * REDES 2                                           *
 *****************************************************/
#ifndef _PACKET_H
#define _PACKET_H

#include "usuario.h"
#include "aviao.h"

/********** OPERACOES *****************/
/* 1 - Pedido de Login                */
/* 2 - Pedido de conexao              */

typedef struct {
  char operacao;
  char IP[20];
  struct usuario usr;
  struct aviao voo;
} Packet;

union PacoteTCP {
	Packet pkt;
	char str[3000];
} pktTCP;

void DieWithError(char *errorMessage);  /* External error handling function */
void servidor();
Packet *envia_cliente_server(Packet* pkt);
void HandleTCPClient(int clntSocket);

#endif /* _PACKET_H */
