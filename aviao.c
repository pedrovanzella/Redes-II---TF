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
    /* TODO: BUG!! Primeiro sempre fica zero? */
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
  char linha[20000];
  char nome[20];
  int ass;
  char pass[20];
  char tmp[4];

  printf("\n\e[1m\e[32mPopulando DB de assentos...\e[0m\n");

  struct aviao* av;

  while((fscanf(assentosfile, "%s", linha) != -1)) 
  {
    int i = 0;

    while(linha[i] != ' ')
    {
      nome[i] = linha[i];
      i++;
    }
    nome[i] = '\0'; // Termina a string para deixar ela limpa
    i++; // Pula o espaco
    av = find_by_voo(nome);

    if(!av)
    {
      fprintf(stderr, "Voo nao encontrado (%s)\n", nome);
      continue;
    }
    printf("\t[x] Voo: %s\n", av->nome);

    /* Copiar assentos */
    while(linha[i] != '\0')
    {
      /* achar numero do assento */ 
      int j = 0;
      while(linha[i] != ':')
      {
        tmp[j] = linha[i]; 
        i++;
        j++;
      }
      tmp[j] = '\0'; // Limpa o fim
      ass = atoi(tmp);
      printf("\t\t[%d] ", ass);

      /* achar o nome do passageiro */
      i++; // Passa os :
      j = 0; // Reseta o contador
      while(linha[i] != ' ')
      {
        pass[j] = linha[i];
        i++;
        j++;
      }
      pass[j] = '\0'; // Limpa a string
      printf("%s\n", pass);
      i++; // Passa o espaco pasa a proxima iteracao

      /* Copia o nome do passageiro para o assento */
      strcpy(av->assentos[ass], pass);
    }

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
