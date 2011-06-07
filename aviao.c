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

extern FILE *voofile;
extern FILE *assentosfile;
extern struct aviao* voos[50];

struct aviao* find_by_voo(char* name)
{

}

void popula_db_voos()
{
    if(!(voofile = fopen("voofile", "r")))
    {
      fprintf(stderr, "popula_db_voos(): Falha ao abrir arquivo de voos!");
      exit(1);
    }
    char name[20];
    int part;
    int cheg;
    char status[20];

    int i = 0;
    while((fscanf(voofile, "%s:%d:%d:%s", name, &part, &cheg, status) != EOF) || i <= 50)
    {
      voos[i] = novo_aviao(name, part, cheg, status);
      i++;
    }
    fclose(voofile);
    popula_assentos();
}

void popula_assentos()
{
  if(!(assentosfile = fopen("assentosfile", "r")))
  {
    fprintf(stderr, "popula_assentos(): Falha ao abrir arquivo de assentos!");
    exit(1);
  }

}

void salva_voo(struct aviao* voo)
{
}

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
