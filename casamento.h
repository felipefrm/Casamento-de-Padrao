#ifndef CASAMENTO
#define CASAMENTO

#define MAXCHAR 256

int ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao);
int ShiftAndAproximado(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao, int k);
int BMH(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao);
int BMHS(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao);

#endif
