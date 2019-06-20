########## Makefile ############

all: main.o entradaSaida.o casamento.o paralelo.o
	gcc entradaSaida.o casamento.o main.o paralelo.o -o tp4 -pthread

main.o: main.c entradaSaida.h casamento.h paralelo.h
	gcc -g -c main.c
entradaSaida.o: entradaSaida.h entradaSaida.c
	gcc -g -c entradaSaida.c
casamento.o: casamento.h casamento.c
	gcc -g -c casamento.c
paralelo.o: paralelo.h paralelo.c
	gcc -g -c paralelo.c
