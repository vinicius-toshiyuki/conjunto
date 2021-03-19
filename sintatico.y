%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lex.yy.h"
#include "tree.h"
#include <assert.h>

#define NAMESIZE 32768

int yylex();
int yyerror(char *s);
void ssprintf(char *target, char *template, ...);
void print(node_t node, void *data);

char filename[512];
char syn_errormsg[NAMESIZE];
extern int lnum, lcol;
node_t root;
%}

%union {
	char name[32768];
	int dval;
	float fval;
	char empty;
}

%type <name> exp
%type <name> idlist
%type <name> arglist
%type <name> argtail
%type <name> parlist
%type <name> partail
%type <name> cmd
%type <name> cmds
%type <name> cmdstail
%type <name> forargs
%type <name> fortail
%token <name> ID TYPE IF WHILE FORALL FOR ELSE RETURN OPPOS OPUNI OPTER
%token <name> OPBIN3 OPBIN4 OPBIN5 OPBIN6 OPBIN7 OPBIN8 OPBIN9 OPBIN10
%token <name> OPASSIGN
%token <name> STRING
%token <name> CHAR
%token <dval> INT
%token <fval> FLOAT
%token <empty> EMPTY

%left OPPOS
%right '!' '~' '&' OPUNI /* ++ -- * & */
%left '*' '/' '%'
%left '+' '-'
%left OPBIN3 /* << >> */
%left OPBIN4 /* > < >= <= */
%left OPBIN5 /* == != */
%left OPBIN6 /* & */
%left OPBIN7 /* ^ */
%left OPBIN8 /* | */
%left OPBIN9 /* && */
%left OPBIN10 /* || */
%right OPTER '?' ':'
%right OPASSIGN

%precedence IF
%precedence ELSE

%%

prog: cmds {
		printf("%s\n", $1);
		depth_pre(print, root, NULL, NULL, NULL);
	}
;

cmds: %empty {
		ssprintf($$, "<block>");
	}
	| cmd cmdstail {
		ssprintf($$, "<block, %s%s>", $1, $2);
	}
;

cmdstail: %empty {
		*$$ = '\0';
	}
	| cmd cmdstail {
		ssprintf($$, ", %s%s", $1, $2);
	}
;

cmd: IF '(' exp ')' cmd %prec IF {
		ssprintf($$, "<%s, %s, %s, <emptycmd>>", $1, $3, $5);
	}
	| IF '(' exp ')' cmd ELSE cmd %prec ELSE {
		ssprintf($$, "<%s, %s, %s, %s>", $1, $3, $5, $7);
	}
	| WHILE '(' exp ')' cmd {
		ssprintf($$, "<%s, %s, %s>", $1, $3, $5);
	}
	| FORALL '(' exp ')' cmd {
		ssprintf($$, "<%s, %s, %s>", $1, $3, $5);
	}
	| FOR '(' forargs ')' cmd {
		ssprintf($$, "<%s, %s, %s>", $1, $3, $5);
	}
	| exp ';' {
		ssprintf($$, "<cmd, %s>", $1);
	}
	| RETURN exp ';' {
		ssprintf($$, "<%s, %s>", $1, $2);
	}
	| '{' cmds '}' {
		strcpy($$, $2);
	}
	| ';' {
		ssprintf($$, "<emptycmd>");
	}
	| TYPE ID idlist ';' {
		ssprintf($$, "<declr, %s, %s%s>", $1, $2, $3);
	}
	| TYPE ID '(' parlist ')' ';' {
		ssprintf($$, "<declr_fn_header, %s, %s%s>", $1, $2, $4);
	}
	| TYPE ID '(' parlist ')' '{' cmds '}' {
		ssprintf($$, "<declr_fn, %s, %s, %s%s>", $1, $2, $7, $4);
	}
	/* Erros */
	| IF '(' error ')' cmd %prec IF {
		ssprintf($$, "<%s, <err_exp>, %s>", $1, $5);
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", $1);
	}
	| IF '(' error ')' cmd ELSE cmd %prec ELSE {
		ssprintf($$, "<%s, <err_exp>, %s, %s>", $1, $5, $7);
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", $1);
	}
	| WHILE '(' error ')' cmd {
		ssprintf($$, "<%s, <err_exp>, %s>", $1, $5);
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", $1);
	}
	| FORALL '(' error ')' cmd {
		ssprintf($$, "<%s, <err_exp>, %s>", $1, $5);
		ssprintf(syn_errormsg, "Expected in-expression in '%s' statment", $1);
	}
	| exp error ';' {
		ssprintf($$, "<err_exp, %s>", $1);
		ssprintf(syn_errormsg, "Expected expression or ';'");
	}
	| RETURN error ';' {
		ssprintf($$, "<err_exp, %s>", $1);
		ssprintf(syn_errormsg, "Expected return expression");
	}
	| TYPE error idlist ';' {
		ssprintf($$, "<err_exp, declr, %s><declr, %s%s>", $1, $1, $3);
		ssprintf(syn_errormsg, "Expected identifier of type '%s'", $1);
	}
;

forargs: TYPE ID '=' exp fortail fortail {
		ssprintf($$, "<forargs, <declr_init, %s, %s, %s>, %s, %s>", $1, $2, $4, $5, $6);
	}
	| TYPE ID fortail fortail {
		ssprintf($$, "<forargs, <declr, %s, %s>, %s, %s>", $1, $2, $3, $4);
	}
	| exp fortail fortail {
		ssprintf($$, "<forargs, %s, %s, %s>", $1, $2, $3);
	}
	| fortail fortail {
		ssprintf($$, "<forargs, <emptyexp>, %s, %s>", $1, $2);
	}
;

fortail: ';' exp {
		ssprintf($$, "%s", $2);
	}
	| ';' {
		strcpy($$, "<emptyexp>");
	}
;

idlist: %empty {
		*$$ = '\0';
	}
	| ',' ID idlist {
		ssprintf($$, ", %s%s", $2, $3);
	}
;

parlist: %empty {
		*$$ = '\0';
	}
	| TYPE ID partail {
		ssprintf($$, ", <par, %s, %s>%s", $1, $2, $3);
	}
	/* Erros */
	| TYPE error partail {
		ssprintf(syn_errormsg, "Expected identifier of type '%s'", $1);
		ssprintf($$, ", <err_par, %s>%s", $1, $3);
	}
;

partail: %empty {
		*$$ = '\0';
	}
	| ',' TYPE ID partail {
		ssprintf($$, "<par, %s, %s>%s", $2, $3, $4);
	}
	/* Erros */
	| error ',' {
		ssprintf(syn_errormsg, "Expected a ','");
		ssprintf($$, "<err_par>");
	}
	| ',' TYPE error ')' {
		ssprintf(syn_errormsg, "Expected identifier of type '%s'", $2);
		ssprintf($$, "<err_par, %s>", $2);
	}
;

exp: INT {
		ssprintf($$, "<int, %d>", $1);
	}
	| FLOAT {
		ssprintf($$, "<float, %f>", $1);
	}
	| EMPTY {
		ssprintf($$, "<empty>");
	}
	| STRING {
		ssprintf($$, "<str, %s>", $1);
	}
	| CHAR {
		ssprintf($$, "<char, %s>", $1);
	}
	| ID OPPOS {
		ssprintf($$, "<exp, <id, %s><oppos, %s>>", $1, $2);
	}
	| '*' exp %prec OPUNI {
		ssprintf($$, "<exp, <opuni, %s>%s>", $<name>1, $2);
	}
	| '+' exp %prec OPUNI {
		ssprintf($$, "<exp, <opuni, %s>%s>", $<name>1, $2);
	}
	| '-' exp %prec OPUNI {
		ssprintf($$, "<exp, <opuni, %s>%s>", $<name>1, $2);
	}
	| '!' exp %prec OPUNI {
		ssprintf($$, "<exp, <opuni, %s>%s>", $<name>1, $2);
	}
	| '~' exp %prec OPUNI {
		ssprintf($$, "<exp, <opuni, %s>%s>", $<name>1, $2);
	}
	| '&' exp %prec OPUNI {
		ssprintf($$, "<exp, <opuni, %s>%s>", $<name>1, $2);
	}
	| OPUNI exp {
		ssprintf($$, "<exp, <opuni, %s>%s>", $1, $2);
	}
	| exp '*' exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $<name>2, $3);
	}
	| exp '/' exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $<name>2, $3);
	}
	| exp '%' exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $<name>2, $3);
	}
	| exp '+' exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $<name>2, $3);
	}
	| exp '-' exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $<name>2, $3);
	}
	| exp OPBIN3 exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $2, $3);
	}
	| exp OPBIN4 exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $2, $3);
	}
	| exp OPBIN5 exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $2, $3);
	}
	| exp OPBIN6 exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $2, $3);
	}
	| exp OPBIN7 exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $2, $3);
	}
	| exp OPBIN8 exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $2, $3);
	}
	| exp OPBIN9 exp {
		ssprintf($$, "<exp, %s<opbin, %s>%s>", $1, $2, $3);
	}
	| exp '?' exp ':' exp {
		ssprintf($$, "<exp, %s<opter, ?>%s<opter, :>%s", $1, $3, $5);
	}
	| ID OPASSIGN exp {
		ssprintf($$, "<exp, <id, %s><opassign, %s>%s>", $1, $2, $3);
	}
	| ID '(' arglist ')' {
		ssprintf($$, "<fn, %s%s>", $1, $3);
	}
	| ID {
		ssprintf($$, "<id, %s>", $1);
	}
	| '(' exp ')' {
		ssprintf($$, "<exp, %s>", $2);
	}
	/* Erros */
	| exp '*' error {
		sprintf(syn_errormsg, "Expected expression while processing '*'");
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $<name>2);
	}
	| exp '/' error {
		sprintf(syn_errormsg, "Expected expression while processing '/'");
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $<name>2);
	}
	| exp '%' error {
		sprintf(syn_errormsg, "Expected expression while processing '%%'");
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $<name>2);
	}
	| exp '+' error {
		sprintf(syn_errormsg, "Expected expression while processing '+'");
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $<name>2);
	}
	| exp '-' error {
		sprintf(syn_errormsg, "Expected expression while processing '-'");
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $<name>2);
	}
	| exp OPBIN3 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $2);
	}
	| exp OPBIN4 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $2);
	}
	| exp OPBIN5 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $2);
	}
	| exp OPBIN6 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $2);
	}
	| exp OPBIN7 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $2);
	}
	| exp OPBIN8 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $2);
	}
	| exp OPBIN9 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>>", $1, $2);
	}
	| exp OPBIN10 error {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2);
		ssprintf($$, "<err_exp, %s<opbin, %s>%s>", $1, $2);
	}
	| ID OPASSIGN error {
		ssprintf(syn_errormsg, "Expected expression in '%s %s'", $1, $2);
		ssprintf($$, "<err_exp, <id, %s><opassign, %s>>", $1, $2);
	}
;

arglist: %empty { *$$ = '\0'; }
	| exp argtail {
		ssprintf($$, ", %s%s", $1, $2);
	}
;

argtail: %empty { *$$ = '\0'; }
	| ',' exp argtail {
		ssprintf($$, ", %s%s", $2, $3);
	}
;

%%

int yyerror(char *s) {
	if (*syn_errormsg) {
		fprintf(stderr, "\033[48;2;145;0;0m  > %s\033[0m\n", syn_errormsg);
	}
	fprintf(stderr, "\033[48;2;145;0;0m%s:%d:%d\033[0m\n", filename, lnum + 1, lcol);
	*syn_errormsg = '\0';
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}
	strcpy(filename, argv[1]);
	root = create_node(filename);
	yyin = fopen(argv[1], "r");
	yyparse();
	if (*syn_errormsg) {
		fprintf(stderr, "\033[48;2;145;0;0m  > %s\033[0m\n", syn_errormsg);
	}
	printf("\n");
	return 0;
}

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsprintf(target, template, ap);
	va_end(ap);
}

void print(node_t node, void *data) {
	int l = level(node);
	for (int i = 0; i < l - 1; i++) {
		printf("  ");
	}
	if (l > 1) {
		printf("|---> ");
	}
	printf("%s\n", (char *) node->value);
}
