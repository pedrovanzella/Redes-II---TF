/********************************************
 * aviao.c                                  *
 * Catiane, Matheus da Rosa, Pedro Vanzella *
 *                                          *
 * REDES 2                                  *
 ********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aviao.h"


struct aviao* novo_aviao(char* n, int p, int c, char* s)
{
  struct aviao* av = (struct aviao*)malloc(sizeof(struct aviao));

  strcpy(av->nome, n);
  av->partida = p;
  av->chegada = c;
  strcpy(av->status, s);

  /* Zerar assentos */
  memset(av->assentos, 0, 150*20);

  return av;
}

struct aviao* reserva_assento(struct aviao* av, int ass, char* user)
{
  /* verifica se assento esta vazio */
  if(!(strcpy(av->assentos[ass], "")))
  {
    strcpy(av->assentos[ass], user); //Copia nome do user para o assento
    return av;
  }
  printf("assento ocupado!\n");
  /* Enviar pacote avisando para o cliente */
  return NULL;
}
