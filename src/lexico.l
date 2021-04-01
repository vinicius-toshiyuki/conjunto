%option nounput noinput noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "sintatico.h"
#include "../include/tree.h"
#include "../include/util.h"

#define YY_USER_ACTION { \
	if (strcmp(errormsg, "")) { \
		if (errlnum == -1 && errlcol == -1) { \
			errlnum = lnum; errlcol = lcol; \
		} \
		if (yy_act != lastrule) { \
			handleError(errormsg, filename_lex, errlnum, errlcol); \
			errlnum = -1; errlcol = -1; \
		} \
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
void handleError(char *msg, char *filename, int lnum, int lcol) {
	fprintf(stderr, ERR_LOCATION, filename, lnum, lcol);
	fprintf(
		stderr,
		ERR_COLOR "  > Invalid character sequence: %s" PARSER_CLEARCOLOR "\n"
		ERR_COLOR ERR_SEPARATOR PARSER_CLEARCOLOR "\n",
		msg
		);
	msg[0] = '\0';
}
%}

ID ([_[:alpha:]][_[:alnum:]]*)
TYPE (int|float|set|elem)

DECIMAL (([[:digit:]]{-}[0])[[:digit:]]*)
HEXA (0[xX][[:xdigit:]]+)
OCTAL (0[0-7]*)
ESCAPE ("\\\\"|"\\0"|"\\a"|"\\b"|"\\t"|"\\n"|"\\v"|"\\f"|"\\r"|"\\e"|"\\"[xX][[:xdigit:]]+|"\\"{OCTAL})

dseq      ([[:digit:]]+)
dseq_opt  ([[:digit:]]*)
frac      (({dseq_opt}"."{dseq})|{dseq}".")
exp       ([eE][+-]?{dseq})
exp_opt   ({exp}?)
fsuff     [flFL]
fsuff_opt ({fsuff}?)
hpref     (0[xX])
hdseq     ([[:xdigit:]]+)
hdseq_opt ([[:xdigit:]]*)
hfrac     (({hdseq_opt}"."{hdseq})|({hdseq}"."))
bexp      ([pP][+-]?{dseq})
dfc       (({frac}{exp_opt}{fsuff_opt})|({dseq}{exp}{fsuff_opt}))
hfc       (({hpref}{hfrac}{bexp}{fsuff_opt})|({hpref}{hdseq}{bexp}{fsuff_opt}))

FLOAT ({dfc}|{hfc})

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
%x expect_char_end
%x expect_err

	char errormsg[512] = "", *filename_lex;
	int noupdate = -1, reading_string = 0;
	int lnum = 1, lcol = 0, lastrule = -1, errlnum = -1, errlcol = -1;

%%

	/* Consome espaços */
<*>"/*"([^*]|"*"[^/])*"*/" /* Consome comentários */
<*>"//"[^\n]*              /* Consome comentários */
<*>{W} if (!reading_string) BEGIN(INITIAL); else yymore();

<INITIAL,expect_err>[\(\){};,] {
	BEGIN(INITIAL);
	RETURNUPDATE yytext[0];
}

if     RETURNUPDATE IF;
else   RETURNUPDATE ELSE;
while  RETURNUPDATE WHILE;
forall RETURNUPDATE FORALL;
for    RETURNUPDATE FOR;
return RETURNUPDATE RETURN;

EMPTY RETURNUPDATE EMPTY;

{TYPE} {
	char *type = strdup(yytext);
	yylval.node = create_node(strdup("<type>"));
	add_child(create_node(type), yylval.node);
	RETURNUPDATE TYPE;
}

{DECIMAL} |
{HEXA}    |
{OCTAL}   {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE INT;
}

{FLOAT} {
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE FLOAT;
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
		case 'i': /* in */ /* TODO: Arrumar a precedência */
			RETURNUPDATE IN;
		case '*':
		case '/':
		case '%':
			RETURNUPDATE yytext[0];
		case '+':
		case '-': RETURNUPDATE yytext[0]; case '<':
		case '>':
			if (strcmp(yytext, "<<") > 0 && strcmp(yytext, ">>") > 1) {
				ret = OPBIN2;
			} else {
				ret = OPBIN1;
			}
			RETURNUPDATE ret;
		case '=':
		case '!':
			RETURNUPDATE OPBIN3; /* Se entrar aqui já deu match em == ou != */
		case '&':
			if (strlen(yytext) > 1) {
				ret = OPBIN7;
			} else {
				ret = OPBIN4;
			}
			RETURNUPDATE ret;
		case '^':
			RETURNUPDATE OPBIN5;
		case '|':
			if (strlen(yytext) > 1) {
				ret = OPBIN8;
			} else {
				ret = OPBIN6;
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

\"/\("\\\""|{ESCAPE}|[^"\\]|{W}\)*\" {
	BEGIN(expect_string);
	reading_string = 1;
	yymore();
}
<expect_string>{W}      |
<expect_string>"\\\""   |
<expect_string>{ESCAPE} |
<expect_string>[^"\\]   { yymore(); }
<expect_string>\" {
	BEGIN(INITIAL);
	reading_string = 0;
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE STRING;
}

'/\("\\'"|{ESCAPE}|[^'\\]\)' {
	BEGIN(expect_char);
	yymore();
}
<expect_char>"\\'"    |
<expect_char>{ESCAPE} |
<expect_char>[^'\\]   {
	BEGIN(expect_char_end);
	yymore();
}
<expect_char_end>' {
	BEGIN(INITIAL);
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE CHAR;
}

	/* Caractere não reconhecido -> Erro */
<*>. {
	strcat(errormsg, yytext);
	BEGIN(expect_err);
}

%%
