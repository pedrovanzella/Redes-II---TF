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

FILE* voofile;
FILE* assentosfile;
extern struct aviao* voos[50];

struct aviao* find_by_voo(char* name)
{

}

void popula_db_voos()
{
  if(!(voofile = fopen("voofile", "r+")))
  {
    fprintf(stderr, "popula_db_voos(): Falha ao abrir arquivo de voos!");
    exit(1);
  }
  char name[20];
  int part;
  int cheg;
  char status[20];
  char tmp[10];

  int i = 0;
  char linha[200];
  while((fscanf(voofile, "%s", linha) != -1) && i <= 50)
  {
    /* achar nome */
    int j = 0;
    while(linha[j] != ':')
    {
      name[j] = linha[j];
      j++;
    }
    name[j] = '\0';

    /* achar partida */
    int k = 0;
    j++;
    while(linha[j] != ':')
    {
      tmp[k] == linha[j];
      j++;
      k++;
    }
    tmp[k] = '\0';
    part = atoi(tmp);

    /* achar chegada */
    k = 0;
    j++;
    while(linha[j] != ':')
    {
      tmp[k] = linha[j];
      j++;
      k++;
    }
    tmp[k] = '\0';
    cheg = atoi(tmp);

    /* achar status */
    k = 0;
    j++;
    while(linha[j] != '\0')
    {
      status[k] = linha[j];
      j++;
      k++;
    }
    status[k] = '\0';

    printf("nome: %s\tpartida: %d\tchegada: %d\tstatus: %s\n", name, part, cheg, status);
    voos[i] = novo_aviao(name, part, cheg, status);
    i++;
  }
  fclose(voofile);
  popula_assentos();
}

void popula_assentos()
{
  if(!(assentosfile = fopen("assentosfile", "r+")))
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
