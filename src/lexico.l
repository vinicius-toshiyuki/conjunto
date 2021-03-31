%option nounput noinput noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "sintatico.h"
#include "../include/tree.h"

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
%x expect_string_end
%x expect_char
%x expect_char_end

	char errormsg[512] = "";
	int noupdate = -1;
	int lnum = 1, lcol = 0, lastrule = -1, errlnum = -1, errlcol = -1;

%%

	/* Consome espaços */
<*>"/*"([^*]|"*"[^/])*"*/" /*  Consome comentários */
<*>"//"[^\n]*              /*  Consome comentários */
<*>{W}                     /*  Consome espaços     */

[\(\){};,] RETURNUPDATE yytext[0];

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
		case 'i': /* in */ /* TODO: Arrumar a precedencia */
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

\"/.*\" { BEGIN(expect_string); yymore(); }
<expect_string>"\\\""   |
<expect_string>{ESCAPE} |
<expect_string>[^"\\]*  {
	BEGIN(expect_string_end);
	yymore();
}
<expect_string_end>\" {
	BEGIN(INITIAL);
	char *val = strdup(yytext);
	yylval.node = create_node(val);
	RETURNUPDATE STRING;
}

' { BEGIN(expect_char); yymore(); }
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
<*>. sprintf(errormsg, "Unexpected character: %s", yytext);

%%
