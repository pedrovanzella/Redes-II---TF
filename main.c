/**********************************************************************/
/*                           main.c                                   */
/*            Ponto de entrada do programa.                           */
/*              Catiane, Matheus da Rosa, Pedro Vanzella              */
/*                                                                    */
/*                          REDES 2                                   */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aviao.h"
#include "usuario.h"
#include "packet.h"

/****************
 * PARAMETROS:  *
 * s : servidor *
 * c : client   *
 ****************/

extern struct usuario* users[50];
extern struct aviao* voos[50];

int main(int argc, char* argv[])
{
  if(argc != 2) /* Testa o numero de parametros de linha de comando */
  {
    fprintf(stderr, "\e[1m\e[32m[x] Inicie com \e[31m%s s \e[32mpara modo servidor ou \e[31m%s c\e[32m para modo cliente\e[0m\n", argv[0], argv[0]);
    return 1;
  }
  if(*argv[1] == 'c')
  {
    /* MODO CLIENTE */

    /********************* CONEXAO *********************/
    printf("Informe IP do servidor: ");
    /* TODO: Verificar validade do formato! */
    Packet* pkt;
    pkt = (Packet*)malloc(sizeof(Packet));
    scanf("%s", pkt->IP);
    pkt->operacao = 2; // Pedido de conexao
    envia_cliente_server(pkt);

    /********************* Log in *********************/
    printf("Informe credenciais (caso nao tenha, informe mesmo assim que serao salvas)\n");
    struct usuario* usr;
    usr = (struct usuario*)malloc(sizeof(struct usuario));
    printf("login: ");
    scanf("%s", usr->nome);
    printf("senha: ");
    scanf("%s", usr->senha);
  }

  if(*argv[1] == 's')
  {
//	Servidor();
//	  return;  
    /* MODO SERVIDOR */
    popula_db_users();
    popula_db_voos();
    /* inicia banco do servidor, lendo arquivo de avioes */
       /* Pede por login */
    char user[20];
    char pass[20];
    strcpy(user, "abs");
    strcpy(pass, "blz");
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
    fprintf(stderr, "Parametro desconhecido (%c). Parametros suportados sao s para servidor ou c para cliente\n", *argv[1]);
    return 1;
  }

  return 0;
}
