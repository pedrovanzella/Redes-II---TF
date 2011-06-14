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
  char nome[20];          /* 20   bytes */
  int partida;            /* 4    bytes */
  int chegada;            /* 4    bytes */
  char status[20];        /* 20   bytes */
  int assentos[150];      /* 150  bytes */
};

struct aviao* voos[50];

struct aviao* novo_aviao(char* n, int p, int c, char* s);
struct aviao* reserva_assento(struct aviao* av, int ass, int usr);
struct aviao* find_by_voo(char* name);
void popula_db_voos();
void popula_assentos();
void salva_voo(struct aviao* voo);
void salva_assento(char* voo, int ass, int pass);

#endif /* _AVIAO_H */
