allg:
	gcc -g -o T_zero *.c

test:
	valgrind --leak-check=full -s ./T_zero

all:
	gcc -c ./funcoesBasicas.c -o ./funcoesBasicas.o
	gcc -c ./funcoesFornecidas.c -o ./funcoesFornecidas.o
	gcc -c ./T_zero.c -o ./T_zero

run:
	./T_zero