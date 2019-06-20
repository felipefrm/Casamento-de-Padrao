#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "casamento.h"
#include "entradaSaida.h"
#include "paralelo.h"

void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag && verificaArqVazio(arq->entrada)) {

    double utime_ant, utime_pos, stime_ant, stime_pos;
    int erro, tamanhoPadrao = 0, tamanhoTexto = 0;
    if(calculaTamanhoStrings(&tamanhoPadrao, &tamanhoTexto, arq->entrada)){

      char *padrao = AlocaString(tamanhoPadrao);
      char *texto = AlocaString(tamanhoTexto);
      leituraStrings(padrao, tamanhoPadrao, texto, tamanhoTexto, arq->entrada);

      printf("P: %d e %d\n", tamanhoPadrao, strlen(padrao));
      // printf("%s\n", padrao);
      printf("T: %d e %d\n", tamanhoTexto, strlen(texto));
      // printf("%s\n", texto);

      printf("Insira o número de erros: (Shift-And Aproximado)\n>>> ");
      scanf("%d", &erro);

      contaTempoProcessador(&utime_ant, &stime_ant);
      BMHSParalelo(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      contaTempoProcessador(&utime_ant, &stime_ant);
      ShiftAnd(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      contaTempoProcessador(&utime_ant, &stime_ant);
      ShiftAndAproximado(texto, strlen(texto), padrao, strlen(padrao), erro, arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      contaTempoProcessador(&utime_ant, &stime_ant);
      BMH(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      contaTempoProcessador(&utime_ant, &stime_ant);
      BMHS(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      liberaStrings(padrao, texto);
    }
  }
  liberaArquivos(arq);
}
