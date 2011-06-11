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

struct usuario* novo_usuario(char* nome, char* senha)
{
  struct usuario* usr = (struct usuario*)malloc(sizeof(struct usuario));
  strcpy(usr->nome, nome);
  strcpy(usr->senha, senha);
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
  char name[20];
  char pass[20];
  int i = 0;
  char linha[50];
  int tmp;
  while(((tmp = fscanf(usrfile, "%s", linha)) != -1) && i <= 50)
  {
    int j = 0;
    int k = 0;
    while(linha[j] != ':')
    {
      name[j] = linha[j];
      j++;
    }
    name[j] = '\0'; //Termina a string para o proximo loop

    j++; // Avancar os :
    while(linha[j] != '\0')
    {
      pass[k] = linha[j]; 
      j++;
      k++;
    }
    pass[k] = '\0';

    printf("nome: %s\tsenha: %s\n", name, pass);
    users[i] = novo_usuario(name, pass);
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
    fprintf(usrfile, "%s", usr->nome);
    fprintf(usrfile, ":%s", usr->senha);
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
  for(i = 0; i <= 50; i++)
  {
    if(!(strcmp(users[i]->nome, name))) 
    {
      return users[i];
    }
  }
  return NULL;
}
