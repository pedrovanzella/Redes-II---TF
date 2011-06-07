/*****************************************************
 * socket.h                                          *
 * Headers das funções do socket TCP    			 *
 * Catiane, Matheus da Rosa, Pedro Vanzella          *
 *                                                   *
 * REDES 2                                           *
 *****************************************************/

/* Receive Functions */
void DieWithError(char *errorMessage);  /* Error handling function */

/* Send Functions */
void HandleTCPClient(int clntSocket);   /* TCP client handling function */