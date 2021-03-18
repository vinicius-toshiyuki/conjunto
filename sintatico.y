%{
#include <stdio.h>
#include "tree.h"
#include <string.h>

int yylex();
int yyerror(char *s);

node_t tree;
node_t current;
char *val;
%}

%union {
	char name[256];
	int dval;
	float fval;
	char empty;
}

%token <name> ID TYPE IF WHILE FORALL FOR ELSE RETURN OPPOS OPUNI OPTER
%token <name> OPBIN3 OPBIN4 OPBIN5 OPBIN6 OPBIN7 OPBIN8 OPBIN9 OPBIN10
%token <name> OPASSIGN
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

%%

prog:
	cmds { tree = create_node(NULL); current = tree; }
;

cmds:
	%empty |
	cmd cmds

cmd:
	IF '(' exp ')' cmd {
		val = (char *) malloc(sizeof(char) * 3);
		strcpy(val, "if");
		current->value = val;
		node_t exp = create_node(NULL);
		node_t cmd = create_node(NULL);
		add_child(exp, current);
		add_child(cmd, current);
		current = exp;
	} |
	WHILE '(' exp ')' cmd {
		val = (char *) malloc(sizeof(char) * 6);
		strcpy(val, "while");
		current->value = val;
		node_t exp = create_node(NULL);
		node_t cmd = create_node(NULL);
		add_child(exp, current);
		add_child(cmd, current);
		current = exp;
	} |
	FORALL '(' exp ')' cmd {
		val = (char *) malloc(sizeof(char) * 7);
		strcpy(val, "forall");
		current->value = val;
		node_t exp = create_node(NULL);
		node_t cmd = create_node(NULL);
		add_child(exp, current);
		add_child(cmd, current);
		current = exp;
	} |
	FOR '(' forargs ')' cmd {
		val = (char *) malloc(sizeof(char) * 4);
		strcpy(val, "for");
		current->value = val;
		node_t arg1 = create_node(NULL);
		node_t arg2 = create_node(NULL);
		node_t arg3 = create_node(NULL);
		node_t cmd = create_node(NULL);
		add_child(arg1, current);
		add_child(arg2, current);
		add_child(arg3, current);
		add_child(cmd, current);
		current = arg1;
	} |
	ELSE cmd {
		val = (char *) malloc(sizeof(char) * 5);
		strcpy(val, "else");
		current->value = val;
		node_t cmd = create_node(NULL);
		add_child(cmd, current);
		current = cmd;
	} |
	exp ';' {
	} |
	RETURN exp ';' {
		val = (char *) malloc(sizeof(char) * 7);
		strcpy(val, "return");
		current->value = val;
		node_t exp = create_node(NULL);
		add_child(exp, current);
		current = exp;
	} |
	'{' cmds '}' {
		val = (char *) malloc(sizeof(char) * 6);
		strcpy(val, "block");
		current->value = val;
		node_t cmds = create_node(NULL);
		add_child(cmds, current);
		current = cmds;
	} |
	TYPE ID idlist ';' {
		val = (char *) malloc(sizeof(char) * 6);
		strcpy(val, "declr");
		current->value = val;
		val = (char *) malloc(sizeof(char) * 5);
		strcpy(val, "type");
		node_t type = create_node(val);
		val = (char *) malloc(sizeof(char) * 3);
		strcpy(val, "id");
		node_t id = create_node(val);
		add_child(type, current);
		add_child(id, current);
	} |
	TYPE ID '(' parlist ')' ';' {
		val = (char *) malloc(sizeof(char) * 8);
		strcpy(val, "fndeclr");
		current->value = val;
		val = (char *) malloc(sizeof(char) * 5);
		strcpy(val, "type");
		node_t type = create_node(val);
		val = (char *) malloc(sizeof(char) * 3);
		strcpy(val, "id");
		node_t id = create_node(val);
		node_t parlist = create_node(NULL);
		add_child(type, current);
		add_child(id, current);
		add_child(parlist, current);
		current = parlist;
	} |
	TYPE ID '(' parlist ')' '{' cmds '}' {
		val = (char *) malloc(sizeof(char) * 8);
		strcpy(val, "fndeclr");
		current->value = val;
		val = (char *) malloc(sizeof(char) * 5);
		strcpy(val, "type");
		node_t type = create_node(val);
		val = (char *) malloc(sizeof(char) * 3);
		strcpy(val, "id");
		node_t id = create_node(val);
		node_t parlist = create_node(NULL);
		node_t cmds = create_node(NULL);
		add_child(type, current);
		add_child(id, current);
		add_child(parlist, current);
		add_child(cmds, current);
		current = parlist;
	}
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
	'*' exp %prec OPUNI |
	'+' exp %prec OPUNI |
	'-' exp %prec OPUNI |
	OPUNI exp |
	exp '*' exp |
	exp '/' exp |
	exp '%' exp |
	exp '+' exp |
	exp '-' exp |
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
	return 0;
}

int main() {
	yyparse();
	printf("\n");
	return 0;
}
