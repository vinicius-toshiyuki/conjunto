SRCS := list.c tree.c sintatico.tab.c lex.yy.c
HEADERS := list.h tree.h sintatico.tab.h lex.yy.h
CFLAGS := -lfl -Wall -g

all: *.l *.y $(SRCS) $(HEADERS)
	flex --header-file=lex.yy.h lexico.l
	bison -d sintatico.y
	gcc -c $(SRCS) $(CFLAGS)
	gcc *.o $(CFLAGS)

clean:
	rm *.o
