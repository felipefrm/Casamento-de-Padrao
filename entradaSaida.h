#ifndef ENTRADASAIDA
#define ENTRADASAIDA

typedef struct arquivos {
  FILE* entrada;
  FILE* saida;
  int flag;   // flag para poder retornar 0 em caso de erro
} Arquivos;

Arquivos* argumentosEntrada(int argc, char* argv[]);
void contaTempoProcessador(double *utime, double *stime);
int verificaArqVazio(FILE* arq);
void imprimeSaida(double user_time, double system_time, int pos, FILE* arq);
void liberaArquivos(Arquivos *arq);

#endif
