all:
	gcc -g -o T_zero *.c
run:
	./T_zero

test:
	valgrind --leak-check=full -s ./T_zero