SRCS := list.c tree.c sintatico.tab.c lex.yy.c
HEADERS := list.h tree.h sintatico.tab.h lex.yy.h
all: *.l *.y $(SRCS) $(HEADERS)
	flex --header-file=lex.yy.h lexico.l
	bison -d sintatico.y
	gcc -c $(SRCS) -lfl
	gcc *.o -lfl

clean:
	rm *.o
