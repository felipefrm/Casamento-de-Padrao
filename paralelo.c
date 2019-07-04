#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "paralelo.h"
#include "entradaSaida.h"

void BMHSParalelo(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq){
  double utime_ant, utime_pos, stime_ant, stime_pos;
  fprintf(arq, "  Casamento(s):");

  if (tamanhoPadrao > tamanhoTexto)     // se padrao > texto retorna pra main sem casamentos
    return;

  int i;
	pthread_t THREADS[NTHREADS];
	thread_arg argument[NTHREADS];

	for(i = 0; i < NTHREADS; i++){

    if(i != 0)
		  argument[i].inicio = argument[i-1].fim+1;
    else
      argument[i].inicio = tamanhoPadrao;

  	argument[i].fim = ((i+1)*tamanhoTexto)/NTHREADS;      // calcula até que parte do texto
    if(argument[0].d[argument[i].fim] < tamanhoPadrao+1)  // a thread vai
      argument[i].fim += argument[0].d[argument[i].fim];

    argument[i].arq = arq;
    argument[i].tamanhoTexto = tamanhoTexto;
    argument[i].tamanhoPadrao = tamanhoPadrao;          // argumentos que serão utilizados
    argument[i].texto = AlocaString(tamanhoTexto);      // em func
    argument[i].padrao = AlocaString(tamanhoPadrao);
    strcpy(argument[i].texto,texto);
    strcpy(argument[i].padrao,padrao);

    // inicia a thread, indicamndo a função "func" e passando os argumentos da thread
		pthread_create(&(THREADS[i]), NULL,func, &(argument[i]));
	}

  for(i = 0; i < NTHREADS; i++)
  // agurada a finalização do thread
		pthread_join(THREADS[i],NULL);

  for(i = 0; i < NTHREADS; i++)
    liberaStrings(argument[i].padrao,argument[i].texto);
}


void *func(void *arg){    // função que executa o BHMS paralelamente com as nthreads

	ptr_thread_arg argument = (ptr_thread_arg) arg;
  int i, k, j = argument->inicio;

  for (i = 0; i <= MAXCHAR; i++)                     // pré - processamento
    argument->d[i] = argument->tamanhoPadrao + 1;
  for (i = 1; i <= argument->tamanhoPadrao; i++)
    argument->d[argument->padrao[i-1]] = argument->tamanhoPadrao - i + 1;

  while (j <= argument->fim) {         // buscando o padrão na fração de texto
    k = j;
    i = argument->tamanhoPadrao;
    while (argument->texto[k-1] == argument->padrao[i-1] && i > 0) {
      k--;
      i--;
    }
    if (i == 0)     // encontrou
      fprintf(argument->arq, " %d", k+1);

    j += argument->d[argument->texto[j]];
  }
}
