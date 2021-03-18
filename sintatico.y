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

%token <name> ID TYPE IF WHILE FORALL FOR ELSE RETURN OPPOS OPUNI OPBIN OPTER
%token <dval> INT
%token <fval> FLOAT
%token <empty> EMPTY

%left OPPOS
%right OPUNI
%left OPBIN /* TODO: Separar */
%right OPTER '?' ':'

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
parlist:
	%empty | TYPE ID partail
;
partail:
	%empty | ',' TYPE ID partail
;

exp:
	INT |
	FLOAT |
	EMPTY |
	ID |
	ID OPPOS |
	OPUNI exp |
	exp OPBIN exp |
	exp '?' exp ':' exp |
	ID '(' arglist ')'
;

arglist:
	%empty | exp argtail
;
argtail:
	%empty | ',' exp argtail
;

%%

int yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
	return 1;
}

int main() {
	yyparse();
	return 0;
}
