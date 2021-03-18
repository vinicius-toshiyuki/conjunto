all: *.l *.y *.c *.h
	flex lexico.l
	bison -d sintatico.y
	gcc -c *.c -lfl
	gcc *.o -lfl
