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
  char nome[20];
  char senha[20];
};

struct usuario* users[50];

struct usuario* novo_usuario(char* nome, char* senha);
struct usuario* login(char* nome, char* senha); /* retorna nulo caso falhe */
struct usuario* find_by_name(char* name);
void popula_db_users();
void salva_user(struct usuario* usr);

#endif /* _USUARIO_H */
