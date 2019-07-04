#include "casamento.h"
#ifndef PARALELO
#define PARALELO

#define NTHREADS 4

typedef struct {
	int inicio;
	int fim;
  FILE* arq;
  int tamanhoPadrao,tamanhoTexto;
  char* texto;
  char* padrao;
	int d[MAXCHAR+1];
} thread_arg, *ptr_thread_arg;

void BMHSParalelo(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq);
void *func(void *arg);

#endif
