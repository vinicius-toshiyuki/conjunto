BUILT_SOURCES = sintatico.h lexico.h
AM_YFLAGS = -d -Wno-yacc -v
bin_PROGRAMS = parser
parser_SOURCES = sintatico.y lexico.l list.c tree.c context.c syntatic_node.c eval.c set.c translation.c util.c builtin.c
parser_CFLAGS = -I../include -std=gnu99 -Wall -g

lexico.h: lexico.l
	$(LEX) --header-file=../include/lexico.h -o lexico.c $<
