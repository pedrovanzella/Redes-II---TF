/*******************************************
 * usuario.c                               *
 * Catina, Matheus da Rosa, Pedro Vanzella *
 *                                         *
 * Redes 2                                 *
 *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

extern struct usuario* users[50];
int users_total;

struct usuario* novo_usuario(int id, char* nome, char* senha)
{
  struct usuario* usr = (struct usuario*)malloc(sizeof(struct usuario));
  usr->id = id;
  strcpy(usr->nome, nome);
  strcpy(usr->senha, senha);
  users_total++;
  printf("\t\tCriei [%d] [%s] [%s]\n", usr->id, usr->nome, usr->senha);
  return usr;
}

void popula_db_users()
{
  FILE* usrfile;
  if(!(usrfile = fopen("usrfile", "r+")))
  {
    fprintf(stderr, "popula_db_users(): Falha ao abrir arquivo de usuarios!");
    exit(1);
  }
  users_total = 0;
  char name[20];
  char pass[20];
  int i = 0;
  char linha[60];
  char tmp[5];
  int id;

  printf("\n\e[1m\e[32mPopulando DB de usuarios...\e[0m\n");

  while(((fscanf(usrfile, "%s", linha)) != -1) && i <= 50)
  {
    int j = 0;
    int k = 0;
    while(linha[j] != ':')
    {
      tmp[j] = linha[j];
      j++;
    }
    tmp[j] = '\0';
    id = atoi(tmp);

    j++;
    k = 0;
    while(linha[j] != ':')
    {
      name[k] = linha[j];
      j++;
      k++;
    }
    name[k] = '\0'; //Termina a string para o proximo loop

    j++; // Avancar os :
    k = 0;
    while(linha[j] != '\0')
    {
      pass[k] = linha[j]; 
      j++;
      k++;
    }
    pass[k] = '\0';

    printf("\tID: %d\tNome: %s\t\tSenha: %s\n", id, name, pass);
    users[i] = novo_usuario(id, name, pass);
    i++;
  }
  fclose(usrfile);
}

void salva_user(struct usuario* usr)
{
  FILE* usrfile;
  if(!(usrfile = fopen("usrfile", "a+")))
  {
    fprintf(stderr, "salva_user(): Falha ao abrir arquivo de usuarios!");
    exit(1);
  }
  if(!find_by_name(usr->nome)) // Se usuario nao existe ainda
  {
    fprintf(usrfile, "%d:%s:%s", usr->id, usr->nome, usr->senha);
  }
  else
  {
    fprintf(stderr, "salva_user(): usuario jah existe!");
  }

  fclose(usrfile);
}

struct usuario* login(char* nome, char* senha)
{
  struct usuario* user;
  user = (struct usuario *) malloc(sizeof(struct usuario));
  user = find_by_name(nome);
  if(!user) // Usuario nao existe
  {
    free(user); // Memory leak
    return NULL; // Se user nao existe
  }
  if(!(strcmp(user->senha, senha))) return user; // Se a senha esta certa
  return NULL; // Senha errada
}

struct usuario* find_by_name(char* name)
{
  int i;
  for(i = 0; i < users_total; i++)
  {
    if(!(strcmp(users[i]->nome, name))) 
    {
      return users[i];
    }
  }
  return NULL;
}

struct usuario* find_by_id(int id)
{
  int i;
  for(i = 0; i < users_total; i++)
  {
    if(users[i]->id == id)
    {
      return users[i];
    }
  }
  return NULL;
}
