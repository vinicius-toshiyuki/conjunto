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
OPJOIN ({OPARIT}=)
OPCOMP ("<="|">="|"<"|">"|"!="|"==")
OPBOOL ("&&"|"||"|"&="|"|="|"&"|"|")
OPUNI ("!"|"-"|"&"|"+"|"~"|"*"|"++"|"--")
OPBIN ({OPJOIN}|{OPARIT}|{OPCOMP}|{OPBOOL}|"="|"in"|"<<"|">>")
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

{ID} {
	printf("<id, %s>", yytext);
	strcpy(yylval.name, yytext);
	return ID;
}

{OPPOS} {
	printf("<opspe, %s>", yytext);
	strcpy(yylval.name, yytext);
	return OPPOS;
}

{OPUNI} {
	printf("<opuni, %s>", yytext);
	strcpy(yylval.name, yytext);
	return OPBIN;
}

{OPBIN} {
	printf("<opbin, %s>", yytext);
	strcpy(yylval.name, yytext);
	return OPBIN;
}

{OPTER} {
	printf("<opter, %s>", yytext);
	strcpy(yylval.name, yytext);
	return OPTER;
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
