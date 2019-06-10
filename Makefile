########## Makefile ############

all: main.o entradaSaida.o casamento.o
	gcc entradaSaida.o casamento.o main.o -o tp4

main.o: main.c entradaSaida.h casamento.h
	gcc -g -c main.c
entradaSaida.o: entradaSaida.h entradaSaida.c
	gcc -g -c entradaSaida.c
casamento.o: casamento.h casamento.c
	gcc -g -c casamento.c
