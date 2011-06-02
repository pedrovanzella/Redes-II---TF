struct usuario
{
  char nome[20];
  char senha[20];
};

struct usuario* novo_usuario(char* nome, char* senha);
struct usuario* login(char* nome, char* senha); /* retorna nulo caso falhe */
