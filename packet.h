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
/* 0 - HELLO                          */
/* 1 - Pedido de Login                */
/* 2 - Login falhou                   */
/* 3 - Sucesso                        */
/* 4 - Falha                          */
/* 5 - Pedido de reserva              */
/* 6 - Pedido de consulta             */
/* 7 - Resposta de consulta           */

typedef struct {
  char operacao;         /* 1   byte  */
  char IP[20];           /* 20  bytes */
  struct usuario usr;    /* 40  bytes */
  struct aviao voo;      /* 198 bytes */
} Packet; /* 259 bytes */


/* 1 Server Envia   */
/* 2 Server Recebe  */
/* 3 Cliente Envia  */
/* 4 Cliente Recebe */
void pacote_pretty_print(Packet* pkt, char op);
void Cliente();
void Servidor();

#endif /* _PACKET_H */
