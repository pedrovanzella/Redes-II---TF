/*****************************************************
 * socket.h                                          *
 * Headers das funções do socket TCP                 *
 * Catiane, Matheus da Rosa, Pedro Vanzella          *
 *                                                   *
 * REDES 2                                           *
 *****************************************************/
#ifndef _SOCKET_H
#define _SOCKET_H

#include "usuario.h"

/********** OPERACOES *****************/
/* 1 - Pedido de Login */
/* 2 - Pedido de conexao */

typedef struct {
  char operacao;
  char* IP;
} Packet;

void DieWithError(char *errorMessage);  /* External error handling function */
int Cliente();
int Servidor();
int envia_cliente_server(Packet* pkt);

#endif /* _SOCKET_H */
