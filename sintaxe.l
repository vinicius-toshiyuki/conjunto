%option stack
%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define YY_USER_ACTION { \
	if (strcmp(errormsg, "") && yy_act != lastrule && preupdate[yy_act]) { \
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
#define YY_USER_INIT { \
	memset(preupdate, 1, YY_NUM_RULES); \
	preupdate[4] = 0; \
	preupdate[5] = 0; \
	preupdate[12] = 0; \
	preupdate[13] = 0; \
	preupdate[15] = 0; \
	preupdate[16] = 0; \
	preupdate[30] = 0; \
	preupdate[31] = 0; \
	preupdate[36] = 0; \
	preupdate[43] = 0; \
	preupdate[46] = 0; \
	preupdate[YY_NUM_RULES - 1] = 0; \
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
int isReserved(char *word) {
	static const char *reserved[] = {
		"if", "else", "while", "for", "forall",
		"int", "float", "set", "elem"
	};
	for (int i = 0; i < sizeof(reserved) / sizeof(const char *); i++) {
		if (!strcmp(reserved[i], word)) return 1;
	}
	return 0;
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
OPCOMP ("<"|">"|"<="|">="|"!="|"==")
OPBOOL ("&&"|"||"|"&"|"|"|"&="|"|=")
OPBIN ({OPARIT}|{OPJOIN}|{OPCOMP}|{OPBOOL}|"="|"in")
OPUNI ("!"|"-")
OPSPE ("++"|"--")

W [ \t\n]+

%x expect_closing
%x expect_cmd
%x expect_par
%x expect_exp
%x expect_exp_par
%x expect_op
%x expect_for
%x expect_fn_declr
%x expect_block
%x expect_declr
%x expect_string
%x expect_char
%x error

	char errormsg[500] = "", preupdate[YY_NUM_RULES];
	int noupdate = -1;
	int lnum = 0, lcol = 0, lastrule = -1, errlnum = -1, errlcol = -1;
	int par_count = 0, brace_count = 0, fargs_count = 0, declaring = 0, precedence_par = 1, mustclose = -1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		/* Consome espaços */
<*>"/*"[*]*[^*]*[*]*"/" /* */
<*>\/{2}[^\n]*$ /* */
<*>{W} /* */
<INITIAL>. {
	noupdate = yy_act;
	printf("<cmd, ");
	yy_push_state(expect_cmd);
	unput(yytext[0]);
}

<expect_closing>. {
	noupdate = yy_act;
	BEGIN(mustclose);
	mustclose = -1;
	printf(">");
	unput(yytext[0]);
}

<expect_cmd>{
	(if|while|forall) {
		mustclose = yy_top_state();
		precedence_par = 0;
		printf("<%s, ", yytext);
		BEGIN(expect_closing);
		yy_push_state(expect_par);
		yy_push_state(expect_exp);
	}
	else {
		mustclose = yy_top_state();
		printf("<else>");
		BEGIN(expect_closing);
	}
	for {
		mustclose = yy_top_state();
		precedence_par = 0;
		printf("<for, ");
		BEGIN(expect_closing);
		yy_push_state(expect_par);
		yy_push_state(expect_for);
		yy_push_state(expect_for);
		yy_push_state(expect_exp);
	}
	; {
		printf(">"); /* Comando vazio (;;;;) */
		yy_pop_state();
	}
	{TYPE}/{W}{ID}{W}?\( { /* Declaração de função */
		printf("<declr_fn, \"%s\", ", yytext);
		yy_push_state(expect_par);
		yy_push_state(expect_fn_declr);
	}
	{TYPE}/{W}{ID}{W}?[,;] { /* Declaração de variável */
		printf("<declr, \"%s\", ", yytext);
		yy_push_state(expect_declr);
	}
	[{}] {
		noupdate = yy_act;
		BEGIN(expect_block);
		unput(yytext[0]);
	}
	. { /* <exp>; */
		noupdate = yy_act;
		yy_push_state(expect_exp);
		unput(yytext[0]);
	}
}

<expect_exp>{
	return/{W} {
		printf("<return>");
	}

	{TYPE} {
		noupdate = yy_act;
		sprintf(errormsg, "Type can not be used as identifier: %s", yytext);
		yy_push_state(error);
		REJECT;
	}

	{CONST}/\( {
		noupdate = yy_act;
		sprintf(errormsg, "Constant is not callable: %s", yytext);
		yy_push_state(error);
		REJECT;
	}

	{INTEGER} {
		printf("<int, %s>", yytext);
		BEGIN(expect_op);
	}
	{FLOAT} {
		printf("<float, %s>", yytext);
		BEGIN(expect_op);
	}
	EMPTY {
		printf("<empty>");
		BEGIN(expect_op);
	}

	{OPUNI}/{VALUE} |
	{OPSPE}/{ID}    {
		printf("<op_uni, \"%s\">", yytext);
	}
	{ID}{OPSPE} {
		printf("<opuni_pos, \"%c%c\">", yytext[yyleng-2], yytext[yyleng-2]);
		int i;
		for (i = yyleng - 3; i >= 0; i--) {
			unput(yytext[i]);
		}
		if (isReserved(yytext)) {
			sprintf(errormsg, "Can not use reserved keyword as identifier: %s", yytext);
			yy_push_state(error);
		}
	}

	{ID}/{W}?\( { /* Chamada de função */
		precedence_par = 0;
		printf("<fn, \"%s\", ", yytext);
		BEGIN(expect_op);
		yy_push_state(expect_par);
		yy_push_state(expect_exp);
		if (isReserved(yytext)) {
			sprintf(errormsg, "Can not use reserved keyword as identifier: %s", yytext);
			yy_push_state(error);
		}
	}

	{ID} {
		printf("<id, \"%s\">", yytext);
		BEGIN(expect_op);
		if (isReserved(yytext)) {
			sprintf(errormsg, "Can not use reserved keyword as identifier: %s", yytext);
			yy_push_state(error);
		}
	}

	\(/{W}?\) {
		par_count++;
		printf("<exp, ");
		BEGIN(expect_op);
	}
	\( {
		if (precedence_par) {
			BEGIN(expect_op);
			yy_push_state(expect_exp_par);
			yy_push_state(expect_exp);
		}
		precedence_par = 1;
		par_count++;
		printf("<exp, ");
	}

	\"/.*\" {
		BEGIN(expect_op);
		yy_push_state(expect_string);
		printf("<str, \"");
	}
	'/.*' {
		BEGIN(expect_op);
		yy_push_state(expect_char);
		printf("<char, '");
	}

	; {
		if (yy_top_state() == expect_for) { /* Fim de uma expressão do for */
			if (yytext[0] == ';') {
				printf(">, <exp, "); /* <for, <exp, ...>, <exp, */
				yy_pop_state();
				yy_pop_state();
				yy_push_state(expect_exp);
			} else {
				sprintf(errormsg, "Unexpected character: %s", yytext);
				yy_push_state(error);
			}
		}
	}
}

<expect_op>{
	\) {
		printf(">"); /* <exp, ...> */
		if (--par_count < 0) {
			par_count++;
			sprintf(errormsg, "Unmatched closing parenthesis: %s", yytext);
			if (yy_top_state() == expect_par || yy_top_state() == expect_exp_par) {
				yy_pop_state();
				yy_pop_state();
			}
			yy_push_state(error);
		} else {
			noupdate = yy_act;
			REJECT;
		}
	}

	[);] {
		yy_pop_state();
		switch (YY_START) {
			case expect_par: /* Fim da expressão do if/while ou última do for */
				if (yytext[0] == ')') {
					printf(">"); /* <if, <exp, ...> etc. */
					yy_pop_state();
				} else {
					yy_push_state(expect_op);
					noupdate = yy_act;
					REJECT;
				}
				break;
			case expect_exp_par: /* Fim de parenteses de precedencia */
				if (yytext[0] == ')') {
					yy_pop_state();
				} else {
					yy_push_state(expect_op);
					noupdate = yy_act;
					REJECT;
				}
				break;
			case expect_for:
				if (yytext[0] == ';') {
					printf(">, <exp, "); /* <for, <exp, ...>, <exp, */
					yy_pop_state();
					yy_push_state(expect_exp);
				} else {
					sprintf(errormsg, "Unexpected character: %s", yytext);
					yy_push_state(error);
				}
				break;
			case expect_cmd: /* Fim de um comando */
				if (yytext[0] == ';') {
					noupdate = yy_act;
					unput(yytext[0]);
				} else {
					REJECT;
				}
				break;
			default: /* Não acabou um comando, então continua */
				yy_push_state(expect_op);
				noupdate = yy_act;
				REJECT;
		}
	}

	{OPBIN}/{W}\(?{VALUE} {
		printf("<op_bin, \"%s\">", yytext);
		BEGIN(expect_exp);
	}

	, {
		printf(", "); /* <exp, ..., " */
		BEGIN(expect_exp);
	}
}

<expect_declr>{
	{ID}/{W}?[,;] {
		printf("%s", yytext);
		declaring = 1;
		if (isReserved(yytext)) {
			sprintf(errormsg, "Can not use reserved keyword as identifier: %s", yytext);
			yy_push_state(error);
		}
	}
	,/{W}?{ID} {
		if (declaring) {
			printf(", ");
		} else {
			sprintf(errormsg, "Expecting identifier in declaration: %s", yytext);
			yy_push_state(error);
		}
	}
	; {
		if (declaring) {
			declaring = 0;
			printf(">");
			yy_pop_state();
			noupdate = yy_act;
			unput(yytext[0]);
		} else {
			sprintf(errormsg, "Expecting identifier in declaration: %s", yytext);
			yy_push_state(error);
		}
	}
}

<expect_fn_declr>{
	{ID}/{W}?\( {
		declaring = 2;
		printf("\"%s\", ", yytext);
		if (isReserved(yytext)) {
			sprintf(errormsg, "Can not use reserved keyword as identifier: %s", yytext);
			yy_push_state(error);
		}
	}
	{TYPE}/{W}{ID}{W}?[,)] {
		declaring = 1;
		fargs_count++;
		printf("<declr, \"%s\", ", yytext);
	}
	{ID}/{W}?[,)] {
		if (declaring == 1) {
			printf("\"%s\">", yytext);
		} else {
			sprintf(errormsg, "Expecting parameter type in definition: %s", yytext);
			yy_push_state(error);
		}
		if (isReserved(yytext)) {
			sprintf(errormsg, "Can not use reserved keyword as identifier: %s", yytext);
			yy_push_state(error);
		}
		declaring = 0;
	}
	\( {
		if (declaring != 2) {
			sprintf(errormsg, "Expecting function name in definition: %s", yytext);
			yy_push_state(error);
		}
		declaring = 0;
	}
	\) {
		fargs_count = 0;
		yy_pop_state();
		if (YY_START == expect_par) {
			printf(">>");
			BEGIN(INITIAL);
			yy_push_state(expect_block);
		} else {
			sprintf(errormsg, "Unexpected closing parenthesis: %s", yytext);
			yy_push_state(error);
			noupdate = yy_act;
			REJECT;
		}
	}
	,/{W}?{TYPE} {
		if (fargs_count == 0 && declaring) {
			sprintf(errormsg, "Expecting parameter definition: %s", yytext);
			yy_push_state(error);
		} else {
			fargs_count++;
			printf(", ");
		}
	}
	[{}] {
		yy_pop_state();
		if (YY_START == expect_par) {
			printf(">>");
			BEGIN(INITIAL);
			yy_push_state(expect_block);
		} else {
			sprintf(errormsg, "Unexpected closing parenthesis: %s", yytext);
			yy_push_state(error);
			noupdate = yy_act;
			REJECT;
		}
		noupdate = yy_act;
		yy_push_state(error);
		sprintf(errormsg, "Expecting closing parenthesis in definition: %s", yytext);
		unput(yytext[0]);
		fargs_count = 0;
	}
}

<expect_block>{
	\{ {
		printf("\n");
		for (int i = 0; i < brace_count; i++) printf("\t");
		brace_count++;
		printf("<block,\n");
		for (int i = 0; i < brace_count; i++) printf("\t");
		printf("<cmd, ");
		yy_push_state(expect_cmd);
	}
	\} {
		if (--brace_count < 0) {
			sprintf(errormsg, "Unmatched closing braces: %s", yytext);
			yy_push_state(error);
		} else {
			printf(">");
			yy_pop_state();
		}
	}
	[^{}] {
		printf("\n");
		for (int i = 0; i < brace_count; i++) printf("\t");
		printf("<cmd, ");
		yy_push_state(expect_cmd);
		noupdate = yy_act;
		unput(yytext[0]);
	}
}

<expect_string>"\\\""|[^"\\]* printf("%s", yytext);
<expect_string>\" {
	printf("\">");
	yy_pop_state();
}

<expect_char>"\\'"|[^'\\] printf("%s", yytext);
<expect_char>' {
	printf("'>");
	yy_pop_state();
}

<*><<eof>> {
	noupdate = yy_act;
	if (par_count != 0) {
		sprintf(errormsg, "Unmatched parenthesis when reached EOF: %s", yytext);
		par_count = 0;
	} else if (brace_count != 0) {
		sprintf(errormsg, "Unmatched braces when reached EOF: %s", yytext);
		brace_count = 0;
	} else {
		return 0;
	}
	yy_push_state(error);
	unput('#');
}


	/* Caractere não reconhecido -> Erro */
<*>. {
	if (YY_START != error) {
		switch (yytext[0]) {
			case '(': par_count++;
				break;
			case ')': par_count--;
				break;
			case '{': brace_count++;
				break;
			case '}': brace_count--;
			default:
				break;
		}
	}
	if (yy_act != lastrule || YY_START == error) {
		errlnum = lnum; errlcol = lcol;
		switch (YY_START) {
			case error:
				yy_pop_state();
				unput(yytext[0]);
				break;
			case expect_cmd:
				sprintf(errormsg, "Expecting a command (if/else/while/for/forall/definition): %s", yytext);
				break;
			case expect_par:
			case expect_exp_par:
				sprintf(errormsg, "Missing parenthesis: %s", yytext);
				break;
			case expect_exp:
				sprintf(errormsg, "Expecting an identifier or literal: %s", yytext);
				break;
			case expect_op:
				sprintf(errormsg, "Expecting an operation: %s", yytext);
				break;
			case expect_for:
				sprintf(errormsg, "Invalid \"for\" argument list: %s", yytext);
				break;
			case expect_fn_declr:
				sprintf(errormsg, "Expecting a function definition: %s", yytext);
				break;
			case expect_declr:
				sprintf(errormsg, "Expecting a variable declaration: %s", yytext);
				break;
			case expect_string:
				sprintf(errormsg, "Missing quotes in string: %s", yytext);
				break;
			case expect_char:
				sprintf(errormsg, "Missing quotes in char: %s", yytext);
				break;
			default:
				sprintf(errormsg, "Unexpected character: %s", yytext);
		}
	} else {
		strcat(errormsg, yytext);
	}
	YY_BREAK;
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main(int argc, char**argv) {
	if (argc < 2) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}
	yyin = fopen(argv[1], "r");
	assert(yyin);
	int ret = yylex();
	printf("\n");
	return ret;
}
