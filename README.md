# Casamento de Padrão

## Resumo

Casamento de padrões é o procedimento de verificação da presença de um padrão em um conjunto de dados. 

Este trabalho prático consiste no estudo dos principais algoritmos de casamento de caracteres. São eles: Shift-And para casamento exato, Boyer-Moore-Horspool (BMH), Boyer-Moore-Horspool-Sunday (BMHS), Shift-And para casamento aproximado, além de uma versão do BMH implementado com programação paralela com o uso de pthread.  


## Passo-a-passo para execução do programa 

1. Compile o programa com o utilitário makefile:
```
  & make
```
2. Execute o programa ./tp4 com o argumento -p seguido do nome do arquivo de padrão, -t seguido do nome do arquivo de texto e -o seguido do nome do arquivo de saída:
```
  & ./tp -p [ARQUIVO DO PADRÃO] -t [ARQUIVO DO TEXTO] -o [ARQUIVO DE SAÍDA]
```
3. Escolha o número de erros permitidos para o Shift-And de casamento aproximado:
```
  &. Insira o número de erros: (Shift-And Aproximado)
   >>>
```
4. Confira a saída do programa no arquivo de saída.
   A saída é composta pela execução de todos os cinco algoritmos junto com o tempo de processamento gasto por eles.
   Ps: No shift-and aproximado é indicado que o casamento ocorre na posição relativa ao fim padrão.
