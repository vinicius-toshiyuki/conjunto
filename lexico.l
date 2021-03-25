%option nounput noinput
%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "sintatico.tab.h"
#include "tree.h"

#define YY_USER_ACTION { \
	if (strcmp(errormsg, "") && yy_act != lastrule) { \
		if (errlnum == -1 && errlcol == -1) { \
			errlnum = lnum; errlcol = lcol; \
		} \
		handleError(errormsg, errlnum, errlcol); \
		errlnum = -1; errlcol = -1; \
	} \
}
#define YY_PREBREAK { \
	if (noupdate != yy_act) { \
		lastrule = yy_act; \
		updatePosition(&lnum, &lcol); \
	} \
}
#define YY_BREAK YY_PREBREAK break;
#define RETURNUPDATE YY_PREBREAK return
// break;
void updatePosition(int *lnum, int *lcol) {
	extern char *yytext;
	extern int yyleng;
	for (int i = 0; i < yyleng; i++) {
		if (yytext[i] == '\n') {
			(*lnum)++;
			*lcol = 0;
		} else (*lcol)++;
	}
}
void handleError(char *msg, int lnum, int lcol) {
	extern char *yytext;
	extern int yyleng;
	fprintf(stderr, "\033[48;2;255;0;0m%s\033[0m\n", msg);
	fprintf(stderr, "\033[48;2;255;0;0mError while processing line %d:%d\033[0m\n", lnum, lcol);
	msg[0] = '\0';
}
%}

ID ([a-zA-Z_][a-zA-Z0-9_]*)
TYPE (int|float|set|elem)

INTEGER (-?[0-9]+)
FLOAT (-?(([0-9]+"."[0-9]*)|[0-9]*"."[0-9]+)f?)|{INTEGER}f
CONST ({INTEGER}|{FLOAT}|EMPTY)
VALUE ({ID}|{CONST})

OPARIT ("*"|"/"|"%"|"+"|"-")
OPCOMP ("<="|">="|"<"|">"|"!="|"==")
OPBOOL ("&&"|"||")
OPBIT ("&"|"^"|"|")
OPUNI ("+"|"-"|"!"|"~"|"++"|"--"|"*"|"&")
OPBIN ({OPARIT}|{OPCOMP}|{OPBOOL}|{OPBIT}|"in"|"<<"|">>")
OPASSIGN (=|{OPARIT}=|{OPBIT}=)
OPTER ("?"|":")
OPPOS ("++"|"--")

W [ \t\n]+

%x expect_string
%x expect_char

	char errormsg[512] = "";
	int noupdate = -1;
	int lnum = 1, lcol = 0, lastrule = -1, errlnum = -1, errlcol = -1;

%%

		/* Consome espaços */
<*>"/*"[*]*[^*]*[*]*"/" /* Consome comentários */
<*>\/{2}[^\n]*$ /* Consome comentários */
<*>{W} /* Consome espaços */

if {
	strcpy(yylval.name, yytext);
	RETURNUPDATE IF;
}
else {
	strcpy(yylval.name, yytext);
	RETURNUPDATE ELSE;
}
while {
	strcpy(yylval.name, yytext);
	RETURNUPDATE WHILE;
}
forall {
	strcpy(yylval.name, yytext);
	RETURNUPDATE FORALL;
}
for {
	strcpy(yylval.name, yytext);
	RETURNUPDATE FOR;
}
return {
	strcpy(yylval.name, yytext);
	RETURNUPDATE RETURN;
}

[\(\){}\[\];,] {
	RETURNUPDATE yytext[0];
}

{TYPE} {
	char *type = strdup(yytext);
	yylval.node = create_node(strdup("<type>"));
	add_child(create_node(type), yylval.node);
	RETURNUPDATE TYPE;
}

{INTEGER} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE INT;
}

{FLOAT} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE FLOAT;
}

EMPTY {
	strcpy(yylval.name, yytext);
	RETURNUPDATE EMPTY;
}

{OPPOS} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE OPPOS;
}

{OPUNI} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	int ret;
	if (strlen(yytext) > 1) {

		ret = OPUNI;
	} else {
		ret = yytext[0];
	}
	RETURNUPDATE ret;
}

{OPBIN} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	int ret;
	switch (yytext[0]) {
		case 'i': /* in */ /* TODO: Arrumar a precedencia */
			RETURNUPDATE IN;
		case '*':
		case '/':
		case '%':
			RETURNUPDATE yytext[0];
		case '+':
		case '-':
			RETURNUPDATE yytext[0];
		case '<':
		case '>':
			if (strcmp(yytext, "<<") > 0 && strcmp(yytext, ">>") > 1) {
				ret = OPBIN4;
			} else {
				ret = OPBIN3;
			}
			RETURNUPDATE ret;
		case '=':
		case '!':
			RETURNUPDATE OPBIN5; /* Se entrar aqui já deu match em == ou != */
		case '&':
			if (strlen(yytext) > 1) {
				ret = OPBIN9;
			} else {
				ret = OPBIN6;
			}
			RETURNUPDATE ret;
		case '^':
			RETURNUPDATE OPBIN7;
		case '|':
			if (strlen(yytext) > 1) {
				ret = OPBIN10;
			} else {
				ret = OPBIN8;
			}
			RETURNUPDATE ret;
		default:
			break;
	}
}

{OPTER} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE yytext[0];
}

{OPASSIGN} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE OPASSIGN;
}

{ID} {
	char *id = strdup(yytext);
	yylval.node = create_node(strdup("<id>"));
	add_child(create_node(id), yylval.node);
	RETURNUPDATE ID;
}

\"/.*\" {
	BEGIN(expect_string);
	yymore();
}
<expect_string>"\\\""|[^"\\]* {
	yymore();
}
<expect_string>\" {
	BEGIN(INITIAL);
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE STRING;
}

'/.*' {
	BEGIN(expect_char);
	yymore();
}
<expect_char>"\\'"|[^'\\] {
	yymore();
}
<expect_char>' {
	BEGIN(INITIAL);
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE CHAR;
}

	/* Caractere não reconhecido -> Erro */
. {
	sprintf(errormsg, "Unexpected character: %s", yytext);
}

%%

// int main(int argc, char**argv) {
// 	if (argc < 2) {
// 		fprintf(stderr, "No input file\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	yyin = fopen(argv[1], "r");
// 	assert(yyin);
// 	int ret = yylex();
// 	printf("\n");
// 	return ret;
// }
