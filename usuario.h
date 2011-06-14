/***********************************************************
 * usuario.h                                               *
 * Declaracao da estrutura de usuario e headers de funcoes *
 * Catiane, Matheus da Rosa, Pedro Vanzella                *
 *                                                         *
 * Redes 2                                                 *
 ***********************************************************/
#ifndef _USUARIO_H
#define _USUARIO_H

struct usuario
{
  int id;          /* 4 bytes  */
  char nome[20];   /* 20 bytes */
  char senha[20];  /* 20 bytes */
}; /* 44 bytes */

struct usuario* users[50];

struct usuario* novo_usuario(int id, char* nome, char* senha);
struct usuario* login(char* nome, char* senha); /* retorna nulo caso falhe */
struct usuario* find_by_name(char* name);
void popula_db_users();
void salva_user(struct usuario* usr);

#endif /* _USUARIO_H */
