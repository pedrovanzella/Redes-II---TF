/*******************************************
 * usuario.c                               *
 * Catina, Matheus da Rosa, Pedro Vanzella *
 *                                         *
 * Redes 2                                 *
 *******************************************/

#include <stdio.h>
#include "usuario.h"

extern struct usuario* users[50];

struct usuario* novo_usuario(char* nome, char* senha)
{

}

struct usuario* login(char* nome, char* senha)
{
  struct usuario* user = find_by_name(nome);
  if(!user) return NULL; // Se user nao existe
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
