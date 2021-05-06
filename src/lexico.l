%option nounput noinput noyywrap
%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "sintatico.h"
#include <tree.h>
#include <syntatic_node.h>
#include <util.h>

#define YY_USER_ACTION {                             \
	if (strcmp(errormsg, "")) {                      \
		if (errlnum == -1 && errlcol == -1) {        \
			errlnum = lnum; errlcol = lcol;          \
		}                                            \
		if (yy_act != lastrule) {                    \
			extern list_t err_loc;                   \
			extern int got_error;                    \
			SET_ERROR_LOCATION(lnum, lcol, err_loc); \
			char *filename = filename_lex;           \
			HANDLE_ERROR(errormsg);                  \
			errormsg[0] = '\0';                      \
			errlnum = -1; errlcol = -1;              \
		}                                            \
	}                                                \
}
#define YY_PREBREAK {                  \
	if (noupdate != yy_act) {          \
		lastrule = yy_act;             \
		update_position(&lnum, &lcol); \
	}                                  \
}
#define YY_BREAK YY_PREBREAK break;
#define RETURNUPDATE YY_PREBREAK return

void update_position(int *lnum, int *lcol) {
	extern char *yytext;
	extern int yyleng;
	for (int i = 0; i < yyleng; i++) {
		if (yytext[i] == '\n') {
			(*lnum)++;
			*lcol = 0;
		} else (*lcol)++;
	}
}

char string_to_char(char *str, char **endptr) {
	char c = *str;
	if (endptr != NULL) {
		*endptr = str + 1;
	}
	if (*str == '\\') {
		long val = -1;
		c = '\r';
		switch (*++str) {
		case 'A':
		case 'a': c--;
		case 'B':
		case 'b': c--;
		case 'T':
		case 't': c--;
		case 'N':
		case 'n': c--;
		case 'V':
		case 'v': c--;
		case 'F':
		case 'f': c--;
		case 'R':
		case 'r':
			if (endptr != NULL) {
				*endptr = str + 1;
			}
			break;
		case 'E':
		case 'e':
			if (endptr != NULL) {
				*endptr = str + 1;
			}
			c = 29;
			break;
		case '\\':
		case '\"':
		case '\'':
			if (endptr != NULL) {
				*endptr = str + 1;
			}
			c = *str;
			break;
		case '0':
			c = '\0';
			if (str[1] != '\0' && !isspace(str[1])) {
				val = strtol(str + 1, endptr, 8);
				if (val > 0xff) {
					fprintf(stderr, "Invalid character range in string_to_char(): %ld\n", val);
					exit(EXIT_FAILURE);
				}
				c = val;
			} else if (endptr != NULL) {
				*endptr = str + 1;
			}
			break;
		case 'x':
		case 'X':
			val = strtol(str + 1, endptr, 16);
			if (val > 0xff) {
				fprintf(stderr, "Invalid character range in string_to_char(): %ld\n", val);
				exit(EXIT_FAILURE);
			}
			c = val;
			break;
		default:
			fprintf(stderr, "Invalid escaped character in string_to_char(): %x\n", *str);
			exit(EXIT_FAILURE);
		}
	}
	return c;
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
OPUNI ("+"|"-"|"!"|"~"|"*"|"&")
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
	int noupdate = -1, reading_string = 0, reading_char = 0;
	int lnum = 1, lcol = 0, lastrule = -1, errlnum = -1, errlcol = -1;

%%

	/* Consome espaços */
<*>"/*"([^*]|"*"[^/])*"*/" /* Consome comentários */
<*>"//"[^\n]*              /* Consome comentários */
<*>{W} {
	if (!reading_string && !reading_char) {
		BEGIN(INITIAL);
	} else if (reading_char) {
		REJECT;
	} else {
		yymore();
	}
}

<INITIAL,expect_err>[\(\){};,] {
	BEGIN(INITIAL);
	RETURNUPDATE yytext[0];
}

if     RETURNUPDATE IF;
else   RETURNUPDATE ELSE;
while  RETURNUPDATE WHILE;
forall RETURNUPDATE FORALL;
for    RETURNUPDATE FOR;
break  RETURNUPDATE BREAK;
return RETURNUPDATE RETURN;

EMPTY RETURNUPDATE EMPTY;

{TYPE} {
	char *typeval = strdup(yytext);
	yylval.node = create_node(create_syn_val(SYN_TAG, TOK_TYPE));
	node_t type = NULL;
	add_child((type = create_node(create_syn_val(SYN_TYPE, typeval))), yylval.node);
	RETURNUPDATE TYPE;
}

{DECIMAL} |
{HEXA}    |
{OCTAL}   {
	char *val = strdup(yytext);

	char *buffer = (char *) malloc(sizeof(char) * 128);
	int intval = (int) strtol(val, NULL, 0);
	sprintf(buffer, "%d", intval);
	buffer = (char *) realloc(buffer, sizeof(char) * (strlen(buffer) + 1));
	free(val);

	yylval.node = create_node(create_syn_val(SYN_EXP, buffer));
	init_syn_exp(CTX_INT, 0, yylval.node->value);
	RETURNUPDATE INT;
}

{FLOAT} {
	char *val = strdup(yytext);

	char *buffer = (char *) malloc(sizeof(char) * 256);
	float floatval= atof(val);
	sprintf(buffer, "%f", floatval);
	buffer = (char *) realloc(buffer, sizeof(char) * (strlen(buffer) + 1));
	free(val);

	yylval.node = create_node(create_syn_val(SYN_EXP, buffer));
	init_syn_exp(CTX_FLOAT, 0, yylval.node->value);
	RETURNUPDATE FLOAT;
}

{OPPOS} {
	char *val = strdup(yytext);
	yylval.node = create_node(create_syn_val(SYN_OP, val));
	init_syn_op(operator_code(val), yylval.node->value);
	RETURNUPDATE OPPOS;
}

{OPUNI} {
	char *val = strdup(yytext);
	yylval.node = create_node(create_syn_val(SYN_OP, val));
	init_syn_op(operator_code(val), yylval.node->value);
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
	yylval.node = create_node(create_syn_val(SYN_OP, val));
	init_syn_op(operator_code(val), yylval.node->value);
	int ret;
	switch (yytext[0]) {
		case 'i': /* in */ /* TODO: Arrumar a precedência */
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
			if (strcmp(yytext, "<<") != 0 && strcmp(yytext, ">>") != 0) {
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
	yylval.node = create_node(create_syn_val(SYN_OP, val));
	init_syn_op(operator_code(val), yylval.node->value);
	RETURNUPDATE yytext[0];
}

{OPASSIGN} {
	char *val = strdup(yytext);
	yylval.node = create_node(create_syn_val(SYN_OP, val));
	init_syn_op(operator_code(val), yylval.node->value);
	RETURNUPDATE OPASSIGN;
}

{ID} {
	char *idval = strdup(yytext);
	yylval.node = create_node(create_syn_val(SYN_TAG, TOK_ID));
	SYN_exp_t id = SYN_EXP(create_syn_val(SYN_EXP, idval));
	init_syn_exp(CTX_UNK, 0, id);
	add_child(create_node(id), yylval.node);
	RETURNUPDATE ID;
}

\"/\("\\\""|{ESCAPE}|[^"\\]|{W}\)*\" {
	BEGIN(expect_string);
	reading_string = 1;
	yymore();
}
<expect_string>"\\\""   |
<expect_string>{ESCAPE} |
<expect_string>[^"\\]   { yymore(); 
}
<expect_string>\" {
	BEGIN(INITIAL);
	reading_string = 0;

	char *val = strdup(yytext);

	char *endptr[1];
	char *strval = (char *) malloc(sizeof(char) * strlen(val) - 1);

	*endptr = val + 1;
	int i = 0;
	do {
		strval[i++] = string_to_char(*endptr, endptr);
	} while (**endptr != '"');
	strval[i] = '\0';
	/* Diminuindo tamanho: garantido que o ponteiro é para o mesmo lugar */
	strval = (char *) realloc(strval, sizeof(char) * (strlen(strval) + 1));

	free(val);
	SYN_exp_t str = SYN_EXP(create_syn_val(SYN_EXP, strval));
	init_syn_exp(CTX_CHAR, 1, str);
	yylval.node = create_node(str);
	RETURNUPDATE STRING;
}

' {
	/* TODO: isso está dando errado??? -> /\("\\'"|{ESCAPE}|[^'\\]\)' */
	reading_char = 1;
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
	reading_char = 0;
	BEGIN(INITIAL);
	char *val = strdup(yytext);

	char *charval = (char *) malloc(sizeof(char) * 2);
	charval[0] = string_to_char(val + 1, NULL);
	charval[1] = '\0';

	free(val);
	SYN_exp_t chr = SYN_EXP(create_syn_val(SYN_EXP, charval));
	init_syn_exp(CTX_CHAR, 0, chr);
	yylval.node = create_node(chr);
	RETURNUPDATE CHAR;
}

	/* Caractere não reconhecido -> Erro */
<*>. {
	if (*errormsg == '\0') {
		strcat(errormsg, "Invalid character sequence: ");
	}
	strcat(errormsg, yytext);
	BEGIN(expect_err);
}

%%
