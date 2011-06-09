/*****************************************************
 * aviao.h                                           *
 * Estrutura de dados e headers de funcoes de avioes *
 * Catiane, Matheus da Rosa, Pedro Vanzella          *
 *                                                   *
 * REDES 2                                           *
 *****************************************************/
#ifndef _AVIAO_H
#define _AVIAO_H

struct aviao
{
  char nome[20];
  int partida;
  int chegada;
  char status[20];
  char assentos[150][20]; /* Cada assento tem um user. 150 assentos de 20 chars */
};

struct aviao* voos[50];

struct aviao* novo_aviao(char* n, int p, int c, char* s);
struct aviao* reserva_assento(struct aviao* av, int ass, char* user);
struct aviao* find_by_voo(char* name);
void popula_db_voos();
void popula_assentos();
void salva_voo(struct aviao* voo);

#endif /* _AVIAO_H */
