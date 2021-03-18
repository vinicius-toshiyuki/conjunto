%option stack
%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "sintatico.tab.h"

#define YY_USER_ACTION { \
	if (strcmp(errormsg, "") && yy_act != lastrule) { \
		if (errlnum == -1 && errlcol == -1) { \
			errlnum = lnum; errlcol = lcol; \
		} \
		handleError(errormsg, errlnum, errlcol); \
		errlnum = -1; errlcol = -1; \
	} \
}
#define YY_BREAK { \
	if (noupdate != yy_act) { \
		lastrule = yy_act; \
		updatePosition(&lnum, &lcol); \
	} \
	break; \
}
void updatePosition(int *lnum, int *lcol) {
	extern char *yytext;
	extern int yyleng;
	for (int i = 0; i < yyleng; i++) {
		if (yytext[i] == '\n') {
			(*lnum)++;
			*lcol = 0;
		}
		(*lcol)++;
	}
}
void handleError(char *msg, int lnum, int lcol) {
	extern char *yytext;
	extern int yyleng;
	fprintf(stderr, "\033[48;2;255;0;0m%s\033[0m\n", msg);
	fprintf(stderr, "\033[48;2;255;0;0mError while processing line %d:%d\033[0m\n", lnum + 1, lcol);
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
	int lnum = 0, lcol = 0, lastrule = -1, errlnum = -1, errlcol = -1;

%%

		/* Consome espaços */
<*>"/*"[*]*[^*]*[*]*"/" /* Consome comentários */
<*>\/{2}[^\n]*$ /* Consome comentários */
<*>{W} /* Consome espaços */

if {
	printf("<cmd, %s>", yytext);
	strcpy(yylval.name, yytext);
	return IF;
}
else {
	printf("<cmd, %s>", yytext);
	strcpy(yylval.name, yytext);
	return ELSE;
}
while {
	printf("<cmd, %s>", yytext);
	strcpy(yylval.name, yytext);
	return WHILE;
}
forall {
	printf("<cmd, %s>", yytext);
	strcpy(yylval.name, yytext);
	return FORALL;
}
for {
	printf("<cmd, %s>", yytext);
	strcpy(yylval.name, yytext);
	return FOR;
}
return {
	printf("<cmd, %s>", yytext);
	strcpy(yylval.name, yytext);
	return RETURN;
}

[\(\){}\[\];,] {
	printf("<%s>", yytext);
	return yytext[0];
}

{TYPE} {
	printf("<type, %s>", yytext);
	strcpy(yylval.name, yytext);
	return TYPE;
}

{INTEGER} {
	printf("<int, %s>", yytext);
	yylval.dval = atoi(yytext);
	return INT;
}

{FLOAT} {
	printf("<float, %s>", yytext);
	yylval.fval = atof(yytext);
	return FLOAT;
}

EMPTY {
	printf("<empty>");
	yylval.empty = 'e';
	return EMPTY;
}

{OPPOS} {
	printf("<op, %s>", yytext);
	strcpy(yylval.name, yytext);
	return OPPOS;
}

{OPUNI} {
	printf("<op, %s>", yytext);
	strcpy(yylval.name, yytext);
	int ret;
	if (strlen(yytext) > 1) {
		ret = OPUNI;
	} else {
		ret = yytext[0];
	}
	return ret;
}

{OPBIN} {
	printf("<op, %s>", yytext);
	strcpy(yylval.name, yytext);
	int ret;
	switch (yytext[0]) {
		case '*':
		case '/':
		case '%':
			return yytext[0];
		case '+':
		case '-':
			return yytext[0];
		case 'i': /* in */ /* TODO: Arrumar a precedencia */
		case '<':
		case '>':
			if (strcmp(yytext, "<<") + strcmp(yytext, ">>") == 1) {
				ret = OPBIN3;
			} else {
				ret = OPBIN4;
			}
			return ret;
		case '=':
		case '!':
			return OPBIN5; /* Se entrar aqui já deu match em == ou != */
		case '&':
			if (strlen(yytext) > 1) {
				ret = OPBIN9;
			} else {
				ret = OPBIN6;
			}
			return ret;
		case '^':
			return OPBIN7;
		case '|':
			if (strlen(yytext) > 1) {
				ret = OPBIN10;
			} else {
				ret = OPBIN8;
			}
			return ret;
		default:
			break;
	}
}

{OPTER} {
	printf("<op, %s>", yytext);
	strcpy(yylval.name, yytext);
	return OPTER;
}

{OPASSIGN} {
	printf("<op, %s>", yytext);
	strcpy(yylval.name, yytext);
	return OPASSIGN;
}

{ID} {
	printf("<id, %s>", yytext);
	strcpy(yylval.name, yytext);
	return ID;
}

\"/.*\" {
	BEGIN(expect_string);
	printf("<str, \"");
}
<expect_string>"\\\""|[^"\\]* printf("%s", yytext);
<expect_string>\" {
	printf("\">");
	BEGIN(INITIAL);
}

'/.*' {
	BEGIN(expect_char);
	printf("<char, '");
}
<expect_char>"\\'"|[^'\\] printf("%s", yytext);
<expect_char>' {
	printf("'>");
	BEGIN(INITIAL);
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
