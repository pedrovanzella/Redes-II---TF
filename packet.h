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
  char operacao;         /* 1  byte  */
  char IP[20];           /* 20 bytes */
  struct usuario usr;    /* 40 bytes */
  struct aviao voo;
} Packet;


void pacote_pretty_print(Packet* pkt);
void Cliente();
void Servidor();

#endif /* _PACKET_H */
