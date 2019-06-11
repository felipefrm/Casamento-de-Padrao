#ifndef CASAMENTO
#define CASAMENTO

#define MAXCHAR 256

void ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq);
void ShiftAndAproximado(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, int k, FILE* arq);
void BMH(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq);
void BMHS(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, FILE* arq);

#endif
