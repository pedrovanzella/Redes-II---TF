/**********************************************************************/
/*                           main.c                                   */
/*            Ponto de entrada do programa.                           */
/*              Catiane, Matheus da Rosa, Pedro Vanzella              */
/*                                                                    */
/*                          REDES 2                                   */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include "token.h"

/****************
 * PARAMETROS:  *
 * s : servidor *
 * c : client   *
 ****************/

struct usuario* users[50];
struct aviao* voos[50];

int main(int argc, char* argv[])
{

  /* MODO CLIENTE */
  /* MODO SERVIDOR */
  /* Pede por login */
  if(login(user, pass))
  {
    /* Usuario logado */ 
    /* imprime prompt de comando */
    char cmd;
    /* grande case de opcoes */

    switch(cmd)
    {
      case 'c': /* Chunky */
        break;
      case 'b': /* Bacon */
        break;
    }
  }

  return 0;
}
