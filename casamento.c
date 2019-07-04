#include <stdio.h>
#include <stdlib.h>
#include "casamento.h"

void BMH(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq) {

  fprintf(arq, "  Casamento(s):");

  if (tamanhoPadrao > tamanhoTexto)     // se padrao > texto retorna pra main sem casamentos
    return;

  int i, j, k, d[MAXCHAR + 1];
  for (i = 0; i <= MAXCHAR; i++)            // pré - processamento
    d[i] = tamanhoPadrao;
  for (i = 1; i < tamanhoPadrao; i++)
    d[padrao[i-1]] = tamanhoPadrao - i;


  j = tamanhoPadrao;
  while (j <= tamanhoTexto) {               // buscando o padrão no texto
    k = j;
    i = tamanhoPadrao;
    while (texto[k-1] == padrao[i-1] && i > 0) {
      k--;
      i--;
    }
    if (i == 0)      // encontrou
      fprintf(arq, " %d", k+1);

    j += d[texto[j-1]];
  }
}


void BMHS(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq) {

  fprintf(arq, "  Casamento(s):");
  if (tamanhoPadrao > tamanhoTexto)     // se padrao > texto retorna pra main sem casamentos
    return;

  int i, j, k, d[MAXCHAR + 1];
  for (i = 0; i <= MAXCHAR; i++)            // pré - processamento
    d[i] = tamanhoPadrao + 1;
  for (i = 1; i <= tamanhoPadrao; i++)
    d[padrao[i-1]] = tamanhoPadrao - i + 1;

  j = tamanhoPadrao;
  while (j <= tamanhoTexto) {               // buscando o padrão no texto
    k = j;
    i = tamanhoPadrao;
    while (texto[k-1] == padrao[i-1] && i > 0) {
      k--;
      i--;
    }
    if (i == 0)     // econtrou
      fprintf(arq, " %d", k+1);

    j += d[texto[j]];
  }
}


void ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq){

  fprintf(arq, "  Casamento(s):");

  if (tamanhoPadrao > tamanhoTexto)     // se padrao > texto retorna pra main sem casamentos
    return;

  int M[MAXCHAR], R = 0;
  for (int i = 0; i < MAXCHAR; i++)       // pré - processamento
    M[i] = 0;
  for (int i = 1; i <= tamanhoPadrao; i++)
    M[padrao[i-1] + 127] |= 1 << (tamanhoPadrao - i);
  for (int i = 0; i < tamanhoTexto; i++) {              // busca pelo padrão no texto
    R = ((R >> 1) | (1 << (tamanhoPadrao - 1))) & M[texto[i] + 127];
    if ((R & 1) != 0){
      if (i - tamanhoPadrao + 2 > 0)  // encontrou
        fprintf(arq, " %d", i - tamanhoPadrao + 2);
    }
  }
}


void ShiftAndAproximado(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, int k, FILE* arq){

  if (k > tamanhoPadrao+1){     // não faz sentido ter um k maior que o tamanho do padrão
    k = tamanhoPadrao+1;        // logo se o usuário digitar um valor maior ele é ajustado
    printf("Erro maior que o tamanho do padrão. Erro ajustado.\n", k);
  }

  fprintf(arq, "  Casamento(s):");

  int M[MAXCHAR], i, j, Ri, Rant, Rnovo;
  int R[tamanhoPadrao + 1];

  for (i = 0; i < MAXCHAR; i++)         // pré - processamento
    M[i] = 0;
  for (i = 1; i <= tamanhoPadrao; i++)
    M[padrao[i-1] + 127] |= 1 << (tamanhoPadrao - i);

  R[0] = 0;
  Ri = 1 << (tamanhoPadrao - 1);

  for (i = 1; i <= k; i++)
    R[i] = (1 << (tamanhoPadrao - i)) | R[i-1];
  for (i = 0; i < tamanhoTexto; i++){  // casamento exato
    Rant = R[0];
    Rnovo = (((Rant) >> 1) | Ri) & M[texto[i] + 127];
    R[0] = Rnovo;
    for (j = 1; j <= k; j++) {         // casamento aproximado
      Rnovo = ((R[j] >> 1) & M[texto[i] + 127]) | Rant | (((Rant | Rnovo)) >> 1);
      Rant = R[j];
      R[j] = Rnovo | Ri;
    }

    if ((Rnovo & 1) != 0)  // encontrou
      if (i+1 > tamanhoPadrao-1)
        fprintf(arq, " %d", i+1);
  }
}
