struct aviao
{
  char nome[20];
  int partida;
  int chegada;
  char status[20];
  char assentos[150][20]; /* Cada assento tem um user. 150 assentos de 20 chars */
};
