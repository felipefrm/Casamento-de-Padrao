#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "casamento.h"
#include "entradaSaida.h"
#include "paralelo.h"

void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  int erro, tamanhoPadrao = 0, tamanhoTexto = 0;
  if (arq->flag && calculaTamanhoStrings(&tamanhoPadrao, &tamanhoTexto, arq->padrao, arq->texto)) {
      double utime_ant, utime_pos, stime_ant, stime_pos;
      char *padrao = AlocaString(tamanhoPadrao);
      char *texto = AlocaString(tamanhoTexto);
      leituraStrings(padrao, tamanhoPadrao, texto, tamanhoTexto, arq->padrao, arq->texto);

      printf("Insira o número de erros: (Shift-And Aproximado)\n>>> ");
      scanf("%d", &erro);

      fprintf(arq->saida, "- BMH\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      BMH(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      fprintf(arq->saida, "- BMHS\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      BMHS(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      fprintf(arq->saida, "- BMHS Paralelo\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      BMHSParalelo(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      fprintf(arq->saida, "- Shift-And Exato\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      ShiftAnd(texto, strlen(texto), padrao, strlen(padrao), arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      fprintf(arq->saida, "- ShiftAnd Aproximado\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      ShiftAndAproximado(texto, strlen(texto), padrao, strlen(padrao), erro, arq->saida);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);

      liberaStrings(padrao, texto);
      liberaArquivos(arq);
  }
}
