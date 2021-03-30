SRCS := list.c tree.c sintatico.tab.c lex.yy.c
HEADERS := list.h tree.h sintatico.tab.h lex.yy.h
CFLAGS := -lfl -Wall -std=gnu99
CDEBUGFLAGS := -g

CC := gcc

all: flex bison $(SRCS) $(HEADERS)
	@echo Compiling sources
	$(CC) -c $(SRCS) $(CFLAGS)
	$(CC) *.o $(CFLAGS)

flex: lexico.l
	@echo Generating lexer
	flex --header-file=lex.yy.h lexico.l

bison: sintatico.y
	@echo Generating parser
	bison -d sintatico.y

debug: flex bison $(SRCS) $(HEADERS)
	@echo Compiling sources with debug flags
	$(CC) -c $(SRCS) $(CFLAGS) $(CDEBUGFLAGS)
	$(CC) *.o $(CFLAGS) $(CDEBUGFLAGS)

clean:
	@echo Removing generated sources
	rm lex.yy.c sintatico.tab.c
	@echo Removing generated objects
	rm *.o
