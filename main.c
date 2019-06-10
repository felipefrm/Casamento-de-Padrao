#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "casamento.h"
#include "entradaSaida.h"

void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag && verificaArqVazio(arq->entrada)) {

    char texto[1000], padrao[1000];
    int posicao, erro;
    double utime_ant, utime_pos, stime_ant, stime_pos;

    // fgets(padrao, sizeof(padrao), arq->entrada);
    // fgets(texto, sizeof(texto), arq->entrada);

    printf("Texto: ");
    setbuf(stdin, NULL);
    gets(texto);
    printf("Padrao: ");
    setbuf(stdin, NULL);
    gets(padrao);

    printf("\nInsira o número de erros: (Shift-And Aproximados)\n>>> ");
    scanf("%d", &erro);

    contaTempoProcessador(&utime_ant, &stime_ant);
    posicao = ShiftAnd(texto, strlen(texto), padrao, strlen(padrao));
    contaTempoProcessador(&utime_pos, &stime_pos);
    printf("posicao = %d\n", posicao);
    imprimeSaida(utime_pos-utime_ant, stime_pos-stime_ant, posicao, arq->saida);

    contaTempoProcessador(&utime_ant, &stime_ant);
    posicao = ShiftAndAproximado(texto, strlen(texto), padrao, strlen(padrao), erro);
    contaTempoProcessador(&utime_pos, &stime_pos);
    printf("posicao = %d\n", posicao);
    imprimeSaida(utime_pos-utime_ant, stime_pos-stime_ant, posicao, arq->saida);

    contaTempoProcessador(&utime_ant, &stime_ant);
    posicao = BMH(texto, strlen(texto), padrao, strlen(padrao));
    contaTempoProcessador(&utime_pos, &stime_pos);
    printf("posicao = %d\n", posicao);
    imprimeSaida(utime_pos-utime_ant, stime_pos-stime_ant, posicao, arq->saida);

    contaTempoProcessador(&utime_ant, &stime_ant);
    posicao = BMHS(texto, strlen(texto), padrao, strlen(padrao));
    contaTempoProcessador(&utime_pos, &stime_pos);
    printf("posicao = %d\n", posicao);
    imprimeSaida(utime_pos-utime_ant, stime_pos-stime_ant, posicao, arq->saida);

    liberaArquivos(arq);
  }
}
