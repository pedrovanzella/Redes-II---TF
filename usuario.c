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
extern FILE *usrfile;

struct usuario* novo_usuario(char* nome, char* senha)
{
  struct usuario* usr = (struct usuario*)malloc(sizeof(struct usuario));
  strcpy(usr->nome, nome, sizeof(nome));
  strcpy(usr->senha, senha, sizeof(senha));
  return usr;
}

void popula_db_users()
{
    if(!(usrfile = fopen("usrfile", "r")))
    {
      fprintf(stderr, "popula_db_users(): Falha ao abrir arquivo de usuarios!");
    }

}

void salva_user()
{

}

struct usuario* login(char* nome, char* senha)
{
  struct usuario* user;
  user = (struct usuario*) malloc(sizeof(struct usuario));
  user = find_by_name(nome);
  if(!user)
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
