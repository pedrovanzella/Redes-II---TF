/**********************************************************************/
/*                           token.h                                  */
/*            Estrutura de dados e headers de funcoes dos tokens      */
/*              Catiane, Matheus da Rosa, Pedro Vanzella              */
/*                                                                    */
/*                          REDES 2                                   */
/*                                                                    */
/**********************************************************************/
#include <netinet/ip.h>

// REMINDER: int inet_ntoa(struct in_addr)

struct token
{
  /* indexar tokenid de zero para manter consistencia! */
  unsigned char tokenid; /* Token ID, temos 256 disponiveis no maximo */
  struct in_addr last_owner_ip; /* ultimo a receber este token */
  struct mac_addr last_owner_mac;
  char free; /* 0 -> token ocupado, 1 -> token livre */
};

struct token tokens[256];

/**************************************************************
 *  give_token(): da um token para o cliente                  *
 *  Se o cliente ja tinha um token, o mesmo eh dado para ele  *
 *  caso contrario, o primeiro token livre sera dado          *
 *  retorna um ponteiro para o token dado                     *
 *  nulo caso nao haja tokens disponiveis                     *
 **************************************************************/
struct token* give_token(struct in_addr client, struct mac_addr machine);
struct token* free_token(struct token* token);
