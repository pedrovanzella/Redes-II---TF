/**********************************************************************/
/*                           token.c                                  */
/*            Implementacao das funcoes de gerenciamento de tokens    */
/*              Catiane, Matheus da Rosa, Pedro Vanzella              */
/*                                                                    */
/*                          REDES 2                                   */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include "token.h"
#include <netinet/ip.h>

extern struct token tokens[256];

struct token* give_token(struct in_addr client, struct mac_addr machine)
{

}

struct token* free_token(struct token* token)
{
}
