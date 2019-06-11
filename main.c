#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "casamento.h"
#include "entradaSaida.h"


void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag && verificaArqVazio(arq->entrada)) {

    int tamanhoPadrao = 0, tamanhoTexto = 0;
    calculaTamanhoStrings(&tamanhoPadrao, &tamanhoTexto, arq->entrada);
    char *padrao = AlocaString(tamanhoPadrao);
    char *texto = AlocaString(tamanhoTexto);

    int erro;
    double utime_ant, utime_pos, stime_ant, stime_pos;

    fgets(padrao, tamanhoPadrao+2, arq->entrada); // le primeira linha até o \n
    padrao[strcspn(padrao, "\n")] = '\0';
    fgets(texto, tamanhoTexto, arq->entrada);

    printf("\nInsira o número de erros: (Shift-And Aproximado)\n>>> ");
    scanf("%d", &erro);

    contaTempoProcessador(&utime_ant, &stime_ant);
    ShiftAnd(texto, tamanhoTexto, padrao, tamanhoPadrao, arq->saida);
    contaTempoProcessador(&utime_pos, &stime_pos);
    imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

    contaTempoProcessador(&utime_ant, &stime_ant);
    ShiftAndAproximado(texto, tamanhoTexto, padrao, tamanhoPadrao, erro, arq->saida);
    contaTempoProcessador(&utime_pos, &stime_pos);
    imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

    contaTempoProcessador(&utime_ant, &stime_ant);
    BMH(texto, tamanhoTexto, padrao, tamanhoPadrao, arq->saida);
    contaTempoProcessador(&utime_pos, &stime_pos);
    imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

    contaTempoProcessador(&utime_ant, &stime_ant);
    BMHS(texto, tamanhoTexto, padrao, tamanhoPadrao, arq->saida);
    contaTempoProcessador(&utime_pos, &stime_pos);
    imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

    liberaStrings(padrao, texto);
  }
  liberaArquivos(arq);
}
