%define lr.type canonical-lr
%parse-param {int *max} {int *childrenCount}
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <locale.h>
#include <wchar.h>
#include "lex.yy.h"
#include <assert.h>
#include "tree.h"

#define NAMESIZE 32768
#define YYDEBUG 1

#define __TREE_WIDE_CHARS__
#ifdef __TREE_WIDE_CHARS__
#define TREECHILDFIRST "┬"
#define TREECHILDMID "├"
#define TREECHILDLAST "└"
#define TREECHILD "│"
#define TREELEAF "○"
#define TREEBRANCH "─"
#else
#define TREECHILDFIRST "."
#define TREECHILDMID "+"
#define TREECHILDLAST "+"
#define TREECHILD "|"
#define TREELEAF ">"
#define TREEBRANCH "-"
#endif

#define ERR_COLOR "145;40;40"
#define ERR_TOKEN "\033[48;2;" ERR_COLOR "m<error>\033[0m"
#define ERR_TEMPLATE "\033[48;2;" ERR_COLOR "m  > %s\033[0m\n\033[48;2;" ERR_COLOR "m====\033[0m\n"
#define ERR_LOCATION "\033[48;2;" ERR_COLOR "m%s:%d:%d\033[0m\n"

int yylex();
int yyerror(int *max, int *childrenCount, char *s);
void ssprintf(char *target, char *template, ...);
void print(node_t node, void *data);
void max_level(node_t node, void *data);
void free_values(node_t node, void *data);

char filename[512];
char syn_errormsg[NAMESIZE];
extern int lnum, lcol;
node_t root;
node_t parent = NULL;
list_t parents;
%}

%code requires {
#include "tree.h"
}

%union {
	char name[32768];
	node_t node;
}

%type <node> exp
%type <node> arglist
%type <node> argtail
%type <node> parlist
%type <node> partail
%type <node> cmd
%type <node> forargs
%type <node> fortail
%token <node> ID TYPE
%token <node> OPPOS OPUNI
%token <node> IN OPBIN3 OPBIN4 OPBIN5 OPBIN6 OPBIN7 OPBIN8 OPBIN9 OPBIN10
%token <node> OPASSIGN
%token <node> STRING
%token <node> CHAR
%token <node> INT
%token <node> FLOAT

%token <name> IF WHILE FORALL FOR ELSE RETURN
%token <name> EMPTY

%right OPASSIGN
%right '?' ':'
%left OPBIN10 /* || */
%left OPBIN9 /* && */
%left OPBIN8 /* | */
%left OPBIN7 /* ^ */
%left OPBIN6 /* & */
%left OPBIN5 /* == != */
%left OPBIN4 /* > < >= <= */
%left OPBIN3 /* << >> */
%left '+' '-'
%left '*' '/' '%'
%left IN
%right '!' '~' '&' OPUNI /* ++ -- * & */
%left OPPOS

%precedence IF
%precedence ELSE

%%

prog: {
		insert(0, root, parents);
	} cmds {
		removeAt(0, parents);
		// fprintf(stderr, "len parents: %lu\n", parents->size);
		// fprintf(stderr, "len root: %lu\n", root->children->size);
		depth_pre(max_level, root, max, NULL, NULL); // Pega a profundidade da árvore
		childrenCount = (int *) calloc(*max, sizeof(int));
		sprintf(root->value, "\033[4m%s\033[0m", (char *) root->value);
		depth_pre(print, root, childrenCount, NULL, NULL);
		free(childrenCount);
		depth_pos(free_values, root, NULL, NULL, NULL);
		delete_node(root);
	}
;

cmds: %empty {}
	| cmd {
		add_child($1, parents->first->value);
	} cmdstail
;

cmdstail: %empty {}
	| cmd {
		add_child($1, parents->first->value);
	} cmdstail
;

cmd: IF '(' exp ')' cmd %prec IF {
		$$ = create_node(strdup("<if>"));
		add_child($3, $$);
		add_child($5, $$);
	}
	| IF '(' exp ')' cmd ELSE cmd %prec ELSE {
		$$ = create_node(strdup("<if-else>"));
		add_child($3, $$);
		add_child($5, $$);
		add_child($7, $$);
	}
	| WHILE '(' exp ')' cmd {
		$$ = create_node(strdup("<while>"));
		add_child($3, $$);
		add_child($5, $$);
	}
	| FORALL '(' exp ')' cmd {
		$$ = create_node(strdup("<forall>"));
		add_child($3, $$);
		add_child($5, $$);
	}
	| FOR {
		$<node>$ = create_node(strdup("<for>"));
		// fprintf(stderr, "Inserindo no for: %lu\n", parents->size);
		insert(0, $<node>$, parents);
	} '(' forargs ')' {
		removeAt(0, parents);
	} cmd {
		$$ = $<node>2;
		add_child($7, $$);
	}
	| exp ';' {
		$$ = $1;
	}
	| RETURN exp ';' {
		$$ = create_node(strdup("<return>"));
		add_child($2, $$);
	}
	| {
		// fprintf(stderr, "Inserindo no {}: %lu\n", parents->size);
		insert(0, create_node(strdup("<block>")), parents);
	} '{' cmds '}' {
		$$ = parents->first->value;
		removeAt(0, parents);
	}
	| ';' {
		$$ = create_node(strdup("<emptycmd>"));
	}
	| TYPE ID {
		$<node>$ = create_node(strdup("<declr>"));
		add_child($1, $<node>$);
		add_child($2, $<node>$);
		// fprintf(stderr, "Inserindo no declr: %lu\n", parents->size);
		insert(0, $<node>$, parents);
	} idlist ';' {
		$$ = $<node>3;
		removeAt(0, parents);
	}
//	| TYPE ID {
//		$<node>$ = create_node(strdup("<declr_fn_header>"));
//		add_child($1, $<node>$);
//		add_child($2, $<node>$);
//
//		node_t pars = create_node(strdup("<parlist>"));
//		add_child(pars, $<node>$);
//		insert(0, pars, parents);
//	} '(' parlist ')' ';' {
//		$$ = $<node>3;
//		removeAt(0, parents);
//		// ssprintf($$, "<declr_fn_header, %s, %s%s>", $1, $2, $4);
//	}
	| TYPE ID '(' {
		$<node>$ = create_node(strdup("<declr_fn>"));
		add_child($1, $<node>$);
		add_child($2, $<node>$);

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, $<node>$);
		// fprintf(stderr, "Inserindo no declr_fn (%s): %lu\n", (char *) ((node_t) $2->children->first->value)->value, parents->size);
		insert(0, pars, parents); /* É removido dentro de declr_fntail */
	} declr_fntail {
		$$ = $<node>4;
	}
	/* Erros */
	| IF '(' error ')' cmd %prec IF {
		$$ = create_node(strdup("<if>"));
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, $$);
		add_child($5, $$);
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", $1);
	}
	| IF '(' error ')' cmd ELSE cmd %prec ELSE {
		$$ = create_node(strdup("<if-else>"));
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, $$);
		add_child($5, $$);
		add_child($7, $$);
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", $1);
	}
	| WHILE '(' error ')' {
		$<node>$ = create_node(strdup("<while>"));
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, $<node>$);
		// add_child($5, $$);
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", $1);
	} cmd {
		$$ = $<node>5;
	}
	| FORALL '(' error ')' {
		$<node>$ = create_node(strdup("<forall>"));
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, $<node>$);
		// add_child($5, $$);
		ssprintf(syn_errormsg, "Expected in-expression in '%s' statment", $1);
	} cmd {
		$$ = $<node>5;
		add_child($6, $$);
	}
	| RETURN error ';' {
		$$ = create_node(strdup("<return>"));
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>2, err);
		add_child(err, $$);
		ssprintf(syn_errormsg, "Expected return expression");
	}
	| TYPE idlist {
		$<node>$ = create_node(strdup("<declr>"));
		add_child($1, $<node>$);
		add_child(create_node(ERR_TOKEN), $<node>$);
		// fprintf(stderr, "Inserindo no declr_error: %lu\n", parents->size);
		insert(0, $<node>$, parents);
	} ';' {
		removeAt(0, parents);
		YYERROR;
	} error {
		$$ = $<node>3;
		ssprintf(syn_errormsg, "Expected identifier of type '%s' lookahead: %c", ((node_t) $1->children->first->value)->value, yychar);
	}
	| TYPE {
		$<node>$ = create_node(strdup("<declr_fn>"));
		add_child($1, $<node>$);
		add_child(create_node(ERR_TOKEN), $<node>$);

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, $<node>$);
		// fprintf(stderr, "Inserindo no declr_fn error: %lu\n", parents->size);
		insert(0, pars, parents);
	} '(' parlist ')' {
		removeAt(0, parents);
		$<node>$ = $<node>2;
		node_t block = create_node(strdup("<block>"));
		add_child(block, $<node>$);
		// fprintf(stderr, "Inserindo no declr_fn {} error: %lu\n", parents->size);
		insert(0, block, parents);
	} '{' cmds '}' {
		removeAt(0, parents);
		YYERROR;
	} error {
		$$ = $<node>6;
		ssprintf(syn_errormsg, "Expected identifier of type '%s' in function declaration", $1->value);
	}
;

declr_fntail: parlist ')' '{' {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);
		// fprintf(stderr, "Inserindo no declr_fn {}: %lu\n", parents->size);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
	} cmds '}' {
		removeAt(0, parents);
	}
	/* Erros */
	| error '{' {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);
		// fprintf(stderr, "Inserindo no declr_fn error 1 {}: %lu\n", parents->size);
		node_t err = create_node(ERR_TOKEN);
		add_child(err, parents->first->value);
		add_child($<node>1, err);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
		ssprintf(syn_errormsg, "Expected a ')'");
		// printf("----------(%s) (%d)\n", $<node>1->value, $<node>1->id);
	} cmds '}' {
		removeAt(0, parents);
	}
	| parlist ')' error ';' {
		node_t err = create_node(ERR_TOKEN);
		node_t block = create_node(strdup("<block>"));
		add_child(err, block);
		add_child(block, ((node_t) parents->first->value)->parent);
		// add_child($<node>3, block);
		// fprintf(stderr, "Inserindo no declr_fn error 2 {}: %lu\n", parents->size);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, err, parents);
		ssprintf(syn_errormsg, "Expected a '{'");
	} cmds '}' {
		removeAt(0, parents);
	}
;

parlist: %empty {}
	| TYPE ID partail {
		add_child($1, parents->first->value);
		add_child($2, parents->first->value);
	}
	/* Erros */
	| ID { /* Missing type */
		add_child(create_node(ERR_TOKEN), parents->first->value);
		add_child($1, parents->first->value);
		YYERROR;
	} partail error {
		ssprintf(syn_errormsg, "Expected a type for '%s'", (char *) ((node_t) $1->children->first->value)->value);
	}
	| TYPE { /* Missing id */
		add_child($1, parents->first->value);
		add_child(create_node(ERR_TOKEN), parents->first->value);
		YYERROR;
	} partail error {
		ssprintf(syn_errormsg, "Expected an identifier of type '%s'", (char *) ((node_t) $1->children->first->value)->value);
	}
;

partail: %empty {}
	| ',' TYPE ID partail {
		add_child($2, parents->first->value);
		add_child($3, parents->first->value);
	}
	/* Erros */
	| TYPE ID partail {
		add_child($1, parents->first->value);
		add_child($2, parents->first->value);
		ssprintf(syn_errormsg, "Expected a ','");
	}
	// | ',' TYPE error ')' {
	// 	add_child($2, parents->first->value);
	// 	add_child(create_node(ERR_TOKEN), parents->first->value);
	// 	// ssprintf($$, "<err_par, %s>", $2);
	// 	ssprintf(syn_errormsg, "Expected identifier of type '%s'", $2->value);
	// }
;

forargs: TYPE ID '=' exp {
		node_t arg = create_node(strdup("<declr_init>"));
		add_child($1, arg);
		add_child($2, arg);
		add_child($4, arg);

		add_child(arg, parents->first->value);
		// fprintf(stderr, "Inserindo no for arg 1: %lu\n", parents->size);
		insert(0, arg, parents);
	} fordeclrlist { /* TODO: Tem que poder fazer várias declarações no for */
		removeAt(0, parents);
	} fortail fortail
	| TYPE ID {
		node_t arg = create_node(strdup("<declr>"));
		add_child($1, arg);
		add_child($2, arg);

		add_child(arg, parents->first->value);
		// fprintf(stderr, "Inserindo no for arg 1: %lu\n", parents->size);
		insert(0, arg, parents);
	} idlist {
		removeAt(0, parents);
	} fortail fortail
	| exp {
		add_child($1, parents->first->value);
	} fortail fortail
	| fortail fortail {
		node_t exp = create_node(strdup("<emptyexp>"));
		exp->parent = parents->first->value;
		insert(0, exp, parents->first->value);
	}
;

fordeclrlist: %empty
	| ',' ID '=' exp fordeclrlist {
		add_child($2, parents->first->value);
		add_child($4, parents->first->value);
	}
;

fortail: ';' exp {
		add_child($2, parents->first->value);
	}
	| ';' {
		add_child(create_node(strdup("<emptyexp>")), parents->first->value);
	}
;

idlist: %empty
	| ',' ID {
		add_child($2, parents->first->value);
	} idlist
	| ',' error {
		node_t err = create_node(ERR_TOKEN);
		add_child(err, parents->first->value);
		add_child($<node>2, err);
		ssprintf(syn_errormsg, "Expected an indentifier");
	} idlist
;

exp: INT {
		node_t aux = create_node(strdup("<int>"));
		add_child($1, aux);
		$$ = aux;
	}
	| FLOAT {
		node_t aux = create_node(strdup("<float>"));
		add_child($1, aux);
		$$ = aux;
	}
	| EMPTY {
		$$ = create_node(strdup("<empty>"));
	}
	| STRING {
		node_t aux = create_node(strdup("<string>"));
		add_child($1, aux);
		$$ = aux;
	}
	| CHAR {
		node_t aux = create_node(strdup("<char>"));
		add_child($1, aux);
		$$ = aux;
	}
	| ID OPPOS {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<oppos>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		$$ = exp;
	}
	| '*' exp %prec OPUNI {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child($<node>1, op);
		add_child(op, exp);
		add_child($2, exp);
		$$ = exp;
	}
	| '+' exp %prec OPUNI {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child($<node>1, op);
		add_child(op, exp);
		add_child($2, exp);
		$$ = exp;
	}
	| '-' exp %prec OPUNI {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child($<node>1, op);
		add_child(op, exp);
		add_child($2, exp);
		$$ = exp;
	}
	| '!' exp %prec OPUNI {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child($<node>1, op);
		add_child(op, exp);
		add_child($2, exp);
		$$ = exp;
	}
	| '~' exp %prec OPUNI {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child($<node>1, op);
		add_child(op, exp);
		add_child($2, exp);
		$$ = exp;
	}
	| '&' exp %prec OPUNI {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child($<node>1, op);
		add_child(op, exp);
		add_child($2, exp);
		$$ = exp;
	}
	| OPUNI exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child($<node>1, op);
		add_child(op, exp);
		add_child($2, exp);
		$$ = exp;
	}
	| exp '*' exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp '/' exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp '%' exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp '+' exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp '-' exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp IN exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp OPBIN3 exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp OPBIN4 exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp OPBIN5 exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp OPBIN6 exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp OPBIN7 exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp OPBIN8 exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp OPBIN9 exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| exp '?' exp ':' exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op1 = create_node(strdup("<opter>"));
		node_t op2 = create_node(strdup("<opter>"));
		add_child($<node>2, op1);
		add_child($<node>4, op2);
		add_child($1, exp);
		add_child(op1, exp);
		add_child($3, exp);
		add_child(op2, exp);
		add_child($5, exp);
		$$ = exp;
	}
	| ID OPASSIGN exp {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		add_child($3, exp);
		$$ = exp;
	}
	| ID {
		$<node>$ = create_node(strdup("<fn>"));
		add_child($1, $<node>$);
		// fprintf(stderr, "Inserindo no fn id: %lu\n", parents->size);
		insert(0, $<node>$, parents);
	} fntail {
		$$ = $<node>2;
		removeAt(0, parents);
	}
	| ID {
		$$ = $1;
	}
	| '(' exp ')' {
		$$ = create_node(strdup("<exp>"));
		add_child($2, $$);
	}
	/* Erros */
	| exp '*' error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		sprintf(syn_errormsg, "Expected expression while processing '*'");
	}
	| exp '/' error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		sprintf(syn_errormsg, "Expected expression while processing '/'");
	}
	| exp '%' error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		sprintf(syn_errormsg, "Expected expression while processing '%%'");
	}
	| exp '+' error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		sprintf(syn_errormsg, "Expected expression while processing '+'");
	}
	| exp '-' error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($<node>2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		sprintf(syn_errormsg, "Expected expression while processing '-'");
	}
	| exp OPBIN3 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| exp OPBIN4 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| exp OPBIN5 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| exp OPBIN6 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| exp OPBIN7 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| exp OPBIN8 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| exp OPBIN9 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| exp OPBIN10 error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", $2->value);
	}
	| ID OPASSIGN error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child($<node>3, err);
		add_child(err, exp);
		$$ = exp;
		ssprintf(syn_errormsg, "Expected expression in '%s %s'", ((node_t) $1->children->first->value)->value, $2->value);
	}
;

fntail: '(' arglist ')'
	| '(' arglist error {
		/* TODO: Incluir algo na árvore? */
		ssprintf(syn_errormsg, "Expected ')'");
	}
;

arglist: %empty {}
	| exp argtail {
		add_child($1, parents->first->value);
	}
;

argtail: %empty {}
	| ',' exp argtail {
		add_child($2, parents->first->value);
	}
;

%%

int yyerror(int *max, int *childrenCount, char *s) {
	if (*syn_errormsg) {
		fprintf(stderr, ERR_TEMPLATE, syn_errormsg);
	}
	fprintf(stderr, ERR_LOCATION, filename, lnum, lcol);
	*syn_errormsg = '\0';
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}
	setlocale(LC_ALL, "");

	strcpy(filename, argv[1]);
	root = create_node(filename);
	parents = create_list();
	int max, *childrenCount = NULL;

	yyin = fopen(argv[1], "r");

	if (yyparse(&max, childrenCount)) {
		fprintf(stderr, "Unhandled error while parsing\n");
		delete_list(parents);
		exit(EXIT_FAILURE);
	}

	if (*syn_errormsg) {
		fprintf(stderr, ERR_TEMPLATE, syn_errormsg);
	}
	return 0;
}

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsprintf(target, template, ap);
	va_end(ap);
}

void print(node_t node, void *data) {
	int *childrenCount = (int *) data;

	int l = level(node);
	childrenCount[l - 1] = node->children->size;
	int isLast = 1;
	if (node->parent != NULL) {
		int idx = indexOf(node, node->parent->children);
		isLast = idx < 0 || idx == node->parent->children->size - 1;
	}
	if (isLast) {
		childrenCount[l - 1] = 0;
	}

	for (int i = 0; i < l - 1; i++) {
		printf("%s ", childrenCount[i] ? TREECHILD : " ");
	}
	if (l > 1) {
		printf(
			"%s" TREEBRANCH "%s" TREEBRANCH TREELEAF " ",
			!isLast ? TREECHILDMID : TREECHILDLAST,
			node->children->size ? TREECHILDFIRST : TREEBRANCH
			);
	}
	printf("%s\n", (char *) node->value);
}

void max_level(node_t node, void *data) {
	int *max = (int *) data;
	int l = level(node);
	if (*max < l) *max = l;
}

void free_values(node_t node, void *data) {
	if (strcmp(node->value, ERR_TOKEN) && strcmp(node->value, filename)) {
		printf("Liberando (%d) (%s) ", node->id, (char *) node->value);
		if (node->parent != NULL)
			printf("Pai (%d) (%s)\n", node->parent->id, (char *) node->parent->value);
		else
			printf("\n");
		free(node->value);
	} else {
		printf("Não liberando (%d) (%s) ", node->id, (char *) node->value);
		if (node->parent != NULL)
			printf("Pai (%d) (%s)\n", node->parent->id, (char *) node->parent->value);
		else
			printf("\n");
	}
}
