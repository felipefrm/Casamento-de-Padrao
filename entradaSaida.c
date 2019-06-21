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
  if (argc < 5){
    fprintf(stderr, "Use: ./tp4 -i [ARQUIVO DE ENTRADA DE DADOS] -o [ARQUIVO DE SAIDA]\n");
    arq->flag = 0;
    return arq;
  }
  while((opcao = getopt(argc, argv, "i:o:"))!= -1) { // recebe-se os argumentos por meio
                                                     // da funcao getopt()
    switch(opcao) {
      case 'i':
        if(!(arq->entrada = fopen(optarg, "r"))) {
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
        break;
      case 'o':
        if(!(arq->saida = fopen(optarg, "w"))) {
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
    }
  }
  return arq;
}


void contaTempoProcessador(double *utime, double *stime){
  struct rusage resources;
  getrusage(RUSAGE_SELF, &resources);
  *utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
  *stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
}


int calculaTamanhoStrings(int* tamanhoPadrao, int* tamanhoTexto, FILE* arq){
  while (fgetc(arq) != '\n')
    (*tamanhoPadrao)++;
  while (fgetc(arq) != EOF)
    (*tamanhoTexto)++;
  rewind(arq);

  if (*tamanhoPadrao == 0 || *tamanhoTexto == 0){
    printf("Padrão ou texto sem conteúdo.\n");
    return 0;
  }
  return 1;
}


char* AlocaString(int tamanho){
  char *str = malloc(sizeof(char)*tamanho);
  return str;
}

void liberaStrings(char* padrao, char* texto){
  free(padrao);
  free(texto);
}


int verificaArqVazio(FILE* arq){
  int tamanho_arq;
  fseek (arq, 0, SEEK_END);               // aponta para o fim do arquivo com fseek()
  if((tamanho_arq = ftell (arq)) == 0){   // retorna o valor da posição do ponteiro com ftell()
    fprintf(stderr, "O arquivo de entrada está vazio!\n");
    return 0;
  }
  rewind(arq);   // retorna o ponteiro para o inicio do arquivo, para os proximos
  return 1;      // procedimentos
}

void leituraStrings(char *padrao, int tamanhoPadrao, char *texto, int tamanhoTexto, FILE *arq){

  // for (i=0; i<tamanhoPadrao; i++)
  //   padrao[i] = fgetc(arq);
  // fgetc(arq); // le o '\n'
  fgets(padrao, tamanhoPadrao+2, arq); // le primeira linha até o \n
  padrao[strcspn(padrao, "\n")] = '\0'; // procura no padrao pelo caractere '\n' e o troca por NULL

  int i;
  for (i=0; i<tamanhoTexto-1; i++)
    texto[i] = fgetc(arq);
  if (texto[i-1] == '\n')
    texto[i-1] = '\0';
}


void imprimeTempo(double user_time, double system_time, FILE* arq){
  fprintf(arq, "\n%fs (tempo de usuário) + %fs (tempo de sistema) = %fs (tempo total)\n\n", user_time, system_time, user_time+system_time);
}

void imprimeCasamento(int pos, FILE* arq){
  if (pos != 0)
    fprintf(arq, "Casamento na posicao: %d\n", pos);
  else
    fprintf(arq, "Não há casamento.\n");
}


void liberaArquivos(Arquivos *arq){
  fclose(arq->entrada);
  fclose(arq->saida);
  free(arq);
}
