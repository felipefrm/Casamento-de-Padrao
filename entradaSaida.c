#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/resource.h>
#include <string.h>
#include "entradaSaida.h"

Arquivos* argumentosEntrada(int argc, char* argv[]){

  Arquivos* arq = malloc(sizeof(Arquivos));   // armazena os ponteiros dos arquivos
  int opcao;
  arq->flag = 1;                              // passados por linha de comando em uma struct
  if (argc < 6){
    fprintf(stderr, "Use: ./tp4 -p [ARQUIVO CONTENDO O PADRÃO] -t [ARQUIVO CONTENDO O TEXTO] -o [ARQUIVO DE SAIDA]\n");
    arq->flag = 0;
    return arq;
  }
  while((opcao = getopt(argc, argv, "p:t:o:"))!= -1) { // recebe-se os argumentos por meio
                                                     // da funcao getopt()
    switch(opcao) {
      case 'p':
        if(!(arq->padrao = fopen(optarg, "r"))) {             // abre arquivo do padrão
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
        break;
      case 't':
        if(!(arq->texto = fopen(optarg, "r"))) {              // abre arquivo do texto
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
        break;
      case 'o':
        if(!(arq->saida = fopen(optarg, "w"))) {              // abre arquivo de saída
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
    }
  }
  return arq;
}


int calculaTamanhoStrings(int* tamanhoPadrao, int* tamanhoTexto, FILE* padrao, FILE *texto){

  while (fgetc(padrao) != EOF)      // le arquivo de padrao e calcula seu tamanho
    (*tamanhoPadrao)++;
  rewind(padrao);

  while (fgetc(texto) != EOF)       // le arquivo de texto e calcula seu tamanho
    (*tamanhoTexto)++;
  rewind(texto);

  //se um deles for igual a 0, retorna 0 e o programa termina
  if (*tamanhoPadrao == 0 || *tamanhoTexto == 0){
    printf("Arquivo de padrão ou texto sem conteúdo.\n");
    return 0;
  }
  return 1;
}


char* AlocaString(int tamanho){
  char *str = malloc(sizeof(char)*tamanho);
  return str;
}


void leituraStrings(char *padrao, int tamanhoPadrao, char *texto, int tamanhoTexto, FILE *arq_padrao, FILE *arq_texto){

  int i;
  for (i=0; i<tamanhoPadrao; i++)     // le o arquivo de padrão, armazendo os caracteres
    padrao[i] = fgetc(arq_padrao);    // no string padrão
  if (padrao[i-1] == '\n')
    padrao[i-1] = '\0';

  for (i=0; i<tamanhoTexto; i++)    // le o arquivo de texto, armazendo os caracteres
    texto[i] = fgetc(arq_texto);    // no string texto
  if (texto[i-1] == '\n')
    texto[i-1] = '\0';

}


void contaTempoProcessador(double *utime, double *stime){
  struct rusage resources;
  getrusage(RUSAGE_SELF, &resources);
  *utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
  *stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
}


void imprimeTempo(double user_time, double system_time, FILE* arq){
  fprintf(arq, "\n  %fs (tempo de usuário) + %fs (tempo de sistema) = %fs (tempo total)\n\n", user_time, system_time, user_time+system_time);
}


void liberaArquivos(Arquivos *arq){
  fclose(arq->padrao);
  fclose (arq->texto);
  fclose(arq->saida);
  free(arq);
}


void liberaStrings(char* padrao, char* texto){
  free(padrao);
  free(texto);
}
