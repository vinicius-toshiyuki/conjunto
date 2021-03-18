%{
#include <stdio.h>

int yylex();
int yyerror(char *s);
%}

%union {
	char name[256];
	int dval;
	float fval;
	char empty;
}

%token <name> ID TYPE IF WHILE FORALL FOR ELSE RETURN OPPOS OPUNI OPTER
%token <name> OPBIN1 OPBIN2 OPBIN3 OPBIN4 OPBIN5 OPBIN6 OPBIN7 OPBIN8 OPBIN9 OPBIN10
%token <name> OPASSIGN
%token <dval> INT
%token <fval> FLOAT
%token <empty> EMPTY

%left OPPOS
%right '+' '-' '!' '~' '*' '&' OPUNI /* ++ -- * & */
%left '+' '/' '%'
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

%%

prog:
	cmds
;

cmds:
	%empty | cmd cmds

cmd:
	IF '(' exp ')' cmd |
	WHILE '(' exp ')' cmd |
	FORALL '(' exp ')' cmd |
	FOR '(' forargs ')' cmd |
	ELSE cmd |
	exp ';' |
	RETURN exp ';' |
	'{' cmds '}' |
	TYPE ID idlist ';' |
	TYPE ID '(' parlist ')' ';' |
	TYPE ID '(' parlist ')' '{' cmds '}'
;

forargs:
	TYPE ID '=' exp fortail fortail |
	TYPE ID fortail fortail |
	exp fortail fortail |
	fortail fortail
;
fortail:
	';' exp |
	';'
;
idlist:
	%empty | ',' ID idlist
;
parlist: %empty
	| TYPE ID partail
;
partail:
	%empty | ',' TYPE ID partail
;

exp:
	INT |
	FLOAT |
	EMPTY |
	ID OPPOS |
	OPUNI exp |
	exp OPBIN1 exp |
	exp OPBIN2 exp |
	exp OPBIN3 exp |
	exp OPBIN4 exp |
	exp OPBIN5 exp |
	exp OPBIN6 exp |
	exp OPBIN7 exp |
	exp OPBIN8 exp |
	exp OPBIN9 exp |
	exp OPBIN10 exp |
	exp '?' exp ':' exp |
	ID OPASSIGN exp |
	ID '(' arglist ')' |
	ID |
	'(' exp ')'
;

arglist:
	%empty | exp argtail
;
argtail:
	%empty | ',' exp argtail
;

%%

int yyerror(char *s) {
	fprintf(stderr, ">> %s\n", s);
	return 1;
}

int main() {
	yyparse();
	printf("\n");
	return 0;
}
