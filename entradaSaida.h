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
char* AlocaString(int tamanho);
void liberaStrings(char* padrao, char* texto);
int calculaTamanhoStrings(int* tamanhoPadrao, int* tamanhoTexto, FILE* arq);
void leituraStrings(char *padrao, int tamanhoPadrao, char *texto, int tamanhoTexto, FILE *arq);
void imprimeTempo(double user_time, double system_time, FILE* arq);
void imprimeCasamento(int pos, FILE* arq);
void liberaArquivos(Arquivos *arq);

#endif
