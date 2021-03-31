BUILT_SOURCES = sintatico.h lexico.h
AM_YFLAGS = -d -Wno-yacc
bin_PROGRAMS = parser
parser_SOURCES = sintatico.y lexico.l list.c tree.c
parser_CFLAGS = -I../include -std=gnu99

lexico.h: lexico.l
	$(LEX) --header-file=../include/lexico.h -o lexico.c $<
