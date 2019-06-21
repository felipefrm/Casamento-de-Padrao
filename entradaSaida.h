#ifndef ENTRADASAIDA
#define ENTRADASAIDA

typedef struct arquivos {
  FILE *padrao;
  FILE *texto;
  FILE* saida;
  int flag;   // flag para poder retornar 0 em caso de erro
} Arquivos;

Arquivos* argumentosEntrada(int argc, char* argv[]);
void contaTempoProcessador(double *utime, double *stime);
int verificaArqVazio(FILE* padrao, FILE* texto);
char* AlocaString(int tamanho);
void liberaStrings(char* padrao, char* texto);
int calculaTamanhoStrings(int* tamanhoPadrao, int* tamanhoTexto, FILE* padrao, FILE *texto);
void leituraStrings(char *padrao, int tamanhoPadrao, char *texto, int tamanhoTexto, FILE *arq_padrao, FILE *arq_texto);
void imprimeTempo(double user_time, double system_time, FILE* arq);
void imprimeCasamento(int pos, FILE* arq);
void liberaArquivos(Arquivos *arq);

#endif
