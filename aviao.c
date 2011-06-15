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
#include "usuario.h"

FILE* voofile;
FILE* assentosfile;
extern struct aviao* voos[50];
int voostotal;

struct aviao* find_by_voo(char* name)
{
  int i;
  for(i = 0; i < voostotal; i++)
  {
    if(!(strcmp(voos[i]->nome, name))) 
    {
      return voos[i];
    }
  }
  return NULL;
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

  printf("\n\e[1m\e[32mPopulando DB de voos...\e[0m\n");

  voostotal = 0;

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
      tmp[k] = linha[j];
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

    printf("\tNome: %s\t\tPartida: %4d\tChegada: %4d\tStatus: %s\n", name, part, cheg, status);
    voos[i] = novo_aviao(name, part, cheg, status);
    i++;
    voostotal++;
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
  char linha[200];
  char nome[20];
  int ass;
  int pass;
  char tmp[4];
  struct usuario* usr;

  printf("\n\e[1m\e[32mPopulando DB de assentos...\e[0m\n");

  struct aviao* av;

  while((fscanf(assentosfile, "%s", linha) != -1)) 
  {
    int i = 0;
    /* Achar nome do voo */
    while(linha[i] != ':')
    {
      nome[i] = linha[i];
      i++;
    }
    nome[i] = '\0';
    i++; // Pular os :

    av = find_by_voo(nome);
    if(!av)
    {
      fprintf(stderr, "popula_assentos(): Aviao nao encontrado (%s)\n", nome);
      continue;
    }
    printf("\tVoo: %s\n", av->nome);

    /* Achar numero do assento */
    int j = 0;
    while(linha[i] != ':')
    {
      tmp[j] = linha[i];
      i++;
      j++;
    }
    tmp[j] = '\0'; // Limpar
    ass = atoi(tmp);
    i++; // Pular os :
    printf("\t\t[%3d] ", ass);

    /* Achar passageiro */
    j = 0;
    while(linha[i] != '\0')
    {
      tmp[j] = linha[i];
      i++;
      j++;
    }
    tmp[j] = '\0'; // Limpar fim da string
    pass = atoi(tmp);
    usr = find_by_id(pass);
    if(!usr)
    {
      printf("[0] Piloto\n");
    }
    else
    {
      printf("[%d] %s\n", pass, usr->nome);
    }

    av->assentos[ass] = pass; // Aloca assento

  }
}

void salva_voo(struct aviao* voo)
{
  if(!(voofile = fopen("voofile", "a+")))
  {
    fprintf(stderr, "salva_voo(): Falha ao abrir arquivo de voos!");
    exit(1);
  }
  fprintf(voofile, "%s:%d:%d:%s", voo->nome, voo->partida, voo->chegada, voo->status);
  fclose(voofile);
}

void salva_assento(char* voo, int ass, int pass)
{
  if(!(assentosfile = fopen("assentosfile", "a+")))
  {
    fprintf(stderr, "salva_assento(): Falha ao abrir arquivo de assentos!");
    exit(1);
  }
  fprintf(assentosfile, "%s:%d:%d", voo, ass, pass);
  fclose(assentosfile);
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

struct aviao* reserva_assento(struct aviao* av, int ass, int user)
{
  /* verifica se assento esta vazio */
  if(av->assentos[ass] == 0)
  {
    av->assentos[ass] = user;
    return av;
  }
  printf("assento ocupado!\n");
  /* Enviar pacote avisando para o cliente */
  return NULL;
}
