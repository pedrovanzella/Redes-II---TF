/*****************************************************
 * socket.h                                          *
 * Headers das funções do socket TCP    			 *
 * Catiane, Matheus da Rosa, Pedro Vanzella          *
 *                                                   *
 * REDES 2                                           *
 *****************************************************/

#include "usuario.h"

typedef struct {
	char operacao; /* 1 - Pedido de Login */
	char *IP;
} Packet;

void DieWithError(char *errorMessage);  /* External error handling function */
int Cliente(Packet *p);
int Servidor();