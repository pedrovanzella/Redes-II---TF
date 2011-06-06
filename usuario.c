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
