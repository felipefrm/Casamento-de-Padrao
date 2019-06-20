#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "paralelo.h"
#include "entradaSaida.h"

void BMHSParalelo(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq){

    int i;
	pthread_t THREADS[NTHREADS];
	thread_arg argument[NTHREADS];
    for(int j=0; j < NTHREADS; j++){
    for (i = 0; i <= MAXCHAR; i++)
      argument[j].d[i] = tamanhoPadrao + 1;
    for (i = 1; i <= tamanhoPadrao; i++)
      argument[j].d[padrao[i-1]] = tamanhoPadrao - i + 1;
}

	for(i = 0; i < NTHREADS; i++){
    if(i != 0)
		  argument[i].inicio = argument[i-1].fim+1;
    else
      argument[i].inicio = tamanhoPadrao;
		argument[i].fim = ((i+1)*tamanhoTexto)/NTHREADS;
    if(argument[0].d[argument[i].fim] < tamanhoPadrao+1)
      argument[i].fim += argument[0].d[argument[i].fim];
    argument[i].arq = arq;
    argument[i].tamanhoTexto = tamanhoTexto;
    argument[i].tamanhoPadrao = tamanhoPadrao;
    argument[i].texto = AlocaString(tamanhoTexto);
    argument[i].padrao = AlocaString(tamanhoPadrao);
    strcpy(argument[i].texto,texto);
    strcpy(argument[i].padrao,padrao);
		pthread_create(&(THREADS[i]), NULL,func, &(argument[i]));
	}
  // printf("\n %s ",argument->texto);
	for(i = 0; i < NTHREADS; i++){
		pthread_join(THREADS[i],NULL);
	}

}
void *func(void *arg){
	ptr_thread_arg argument = (ptr_thread_arg) arg;
  int flag = 0, i, k, j = argument->inicio;
  while (j <= argument->fim) {
    // printf("\n %s ",argument->texto);
    k = j;
    i = argument->tamanhoPadrao;
    while (argument->texto[k-1] == argument->padrao[i-1] && i > 0) {
      k--;
      i--;
    }
    if (i == 0){
      flag = 1;
      fprintf(argument->arq, "Casamento na posicao: %d\n", k+1);
    }
    j += argument->d[argument->texto[j]];
  }
  if (flag == 0)
    fprintf(argument->arq, "Não há casamento.\n");
}
// void BMHS(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq) {
//
//   int i, j, k, d[MAXCHAR + 1], flag = 0;
//   for (i = 0; i <= MAXCHAR; i++)
//     d[i] = tamanhoPadrao + 1;
//   for (i = 1; i <= tamanhoPadrao; i++)
//     d[padrao[i-1]] = tamanhoPadrao - i + 1;
//
//   j = tamanhoPadrao;
//   while (j <= tamanhoTexto) {
//     k = j;
//     i = tamanhoPadrao;
//     while (texto[k-1] == padrao[i-1] && i > 0) {
//       k--;
//       i--;
//     }
//     if (i == 0) {
//       flag = 1;
//       fprintf(arq, "Casamento na posicao: %d\n", k+1);
//     }
//     j += d[texto[j]];
//   }
//   if (flag == 0)
//     fprintf(arq, "Não há casamento.\n");
// }
