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
    /********************* INICIALIZAR *********************/
    Packet* pkt;
    pkt = (Packet*)malloc(sizeof(Packet));
    memset(pkt, '\0', sizeof(Packet));

    /********************* CONEXAO *********************/
    printf("Informe IP do servidor: ");
    /* TODO: Verificar validade do formato! */
    scanf("%s", pkt->IP);
    pkt->operacao = 2; // Pedido de conexao
    //envia_cliente_server(pkt);
    pacote_pretty_print(pkt);

    /********************* Log in *********************/
    printf("Informe credenciais (caso nao tenha, informe mesmo assim que serao salvas)\n");
    printf("login: ");
    scanf("%s", pkt->usr.nome);
    printf("senha: ");
    scanf("%s", pkt->usr.senha);
    pkt->operacao = 1; // Pedido de Login
    pacote_pretty_print(pkt);

    /********************* Espera servidor *********************/
  }

  else if(*argv[1] == 's')
  {
    /* MODO SERVIDOR */
    /********************* INICIALIZAR *********************/
    popula_db_users();
    popula_db_voos();

    /********************* Espera cliente *********************/
    servidor();

  }

  else /* parametro errado */
  {
    fprintf(stderr, "Parametro desconhecido (%c). Parametros suportados sao s para servidor ou c para cliente\n", *argv[1]);
    return 1;
  }

  return 0;
}
