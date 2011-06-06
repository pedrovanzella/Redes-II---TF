/**********************************************************************/
/*                           main.c                                   */
/*            Ponto de entrada do programa.                           */
/*              Catiane, Matheus da Rosa, Pedro Vanzella              */
/*                                                                    */
/*                          REDES 2                                   */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include "aviao.h"
#include "usuario.h"

/****************
 * PARAMETROS:  *
 * s : servidor *
 * c : client   *
 ****************/

struct usuario* users[50];
struct aviao* voos[50];

int main(int argc, char* argv[])
{
  if(argc < 2) /* Testa o numero de parametros de linha de comando */
  {
    fprintf(stderr, "\e[1m\e[33m[x] Inicie com %s s para modo servidor ou %s c para modo cliente", argv[0], argv[0]);
    return 1;
  }
  if(*argv[1] == 'c')
  {
    /* MODO CLIENTE */
  }

  if(*argv[1] == 's')
  {
    /* MODO SERVIDOR */
    /* inicia banco do servidor, lendo arquivo de avioes */
    /* Pede por login */
    char* user, pass;
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
  }
  else /* parametro errado */
  {
    fprintf(stderr, "Parametro desconhecido (%c). Parametros suportados sao s para servidor ou c para cliente", argv[1]);
    return 1;
  }

  return 0;
}
