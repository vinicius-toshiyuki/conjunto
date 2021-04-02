%define lr.type canonical-lr

/* Parâmetros para a função yyparse() */
%parse-param {int *max} {int *childrenCount}

%{ /* ================== INÍCIO DO PREFÁCIO ===================== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <lexico.h>
#include <tree.h>
#include <util.h>

#define NAMESIZE 32768
#define FILENAMESIZE 512

/* ========================= Macros ============================= */
#define ADD_BIN_EXP(RES, EXP1, OP, EXP2) {      \
	node_t exp = create_node(strdup("<exp>"));  \
	node_t op = create_node(strdup("<opbin>")); \
	add_child(OP, op);                          \
	add_child(EXP1, exp);                       \
	add_child(op, exp);                         \
	add_child(EXP2, exp);                       \
	RES = exp;                                  \
}

#define ADD_BIN_EXP_ERR(RES, EXP1, OP) {        \
	node_t exp = create_node(strdup("<exp>"));  \
	node_t op = create_node(strdup("<opbin>")); \
	add_child(OP, op);                          \
	add_child(EXP1, exp);                       \
	add_child(op, exp);                         \
	node_t err = create_node(ERR_TOKEN);        \
	add_child(err, exp);                        \
	RES = exp;                                  \
	ssprintf(                                   \
		syn_errormsg,                           \
		"Expected expression before '%s'",      \
		OP->value                               \
		);                                      \
}

#define ADD_UNI_EXP(RES, OP, EXP1) {            \
	node_t exp = create_node(strdup("<exp>"));  \
	node_t op = create_node(strdup("<opuni>")); \
	add_child(OP, op);                          \
	add_child(op, exp);                         \
	add_child(EXP1, exp);                       \
	RES = exp;                                  \
}

#define FIRSTCHILD_VALUE(NODE) \
	((char *) ((node_t) NODE->children->first->value)->value)

#define PUSH_CONTEXT {                            \
	node_t OLD_CONTEXT = current_context;         \
	current_context = create_node(create_list()); \
	add_child(current_context, OLD_CONTEXT);      \
}

#define POP_CONTEXT \
	current_context = current_context->parent;

enum {
	FUN,
	VAR
};
#define ADD_CONTEXT(ENTRY_CONTEXT, ID_CONTEXT, TYPE_CONTEXT) {     \
	char TEMPLATE[] = "<%s '%s' (%s)>";                            \
	char *ENTRY, *ENTRYTYPE;                                       \
	char FUNCTION[] = "function", VARIABLE[] = "variable";         \
	switch (ENTRY_CONTEXT) {                                       \
	case FUN: ENTRYTYPE = FUNCTION; break;                         \
	case VAR: ENTRYTYPE = VARIABLE; break;                         \
	default:                                                       \
	fprintf(stderr, "Invalid entry type in context\n");            \
	exit(EXIT_FAILURE);                                            \
	}                                                              \
	ENTRY = (char *) malloc(                                       \
	strlen(TEMPLATE) +                                             \
	strlen(ENTRYTYPE) +                                            \
	strlen(ID_CONTEXT) +                                           \
	strlen(TYPE_CONTEXT) + 1                                       \
	);                                                             \
	sprintf(ENTRY, TEMPLATE, ENTRYTYPE, ID_CONTEXT, TYPE_CONTEXT); \
	insert(0, ENTRY, current_context->value);                      \
}

/* ============================================================== */

/* Estrutura para passar argumentos para impressão */
typedef struct {
	int *childrenCount;
	void (*val_print)(node_t value);
} printData_t;

/* Assinatura dependente do %parse-param */
int yyerror(int *max, int *childrenCount, char *s);
int yylex();

void ssprintf(char *target, char *template, ...); /* É a mesma coisa do sprintf() */
void print(node_t node, void *data);              /* Imprime um nó de uma árvore */
void print_syntatic(node_t value);                /* Imprime o valor de um nó da árvore sintática */
void print_context(node_t value);                 /* Imprime o valor de um nó do contexto */
void max_level(node_t node, void *data);          /* Obtém a profundidade de uma árvore */
void free_values(node_t node, void *data);        /* Libera a memória do valor de um nó */
void free_context(node_t node, void *data);       /* Libera a memória de um context */

extern int lnum, lcol; /* Vêm do lexico.l */

char filename[FILENAMESIZE + 1]; /* Armazena o nome do arquivo de entrada */
char syn_errormsg[NAMESIZE + 1]; /* Armazena a próxima mensagem de erro */

node_t root;    /* Raiz da árvore sintática */
list_t parents; /* Auxilia na inserção na árvore */

node_t current_context;
node_t context; /* Árvore de contextos */
%}
/* ======================= FIM DO PREFÁCIO ====================== */

%code requires {
#include "tree.h"
}

%union {
	char name[32768];
	node_t node;
}

%destructor {
	depth_pre(free_values, $$, NULL, NULL, NULL);
	delete_node($$);
} <node>

/* ============== Definições de tokens e tipos ========== /**/
%type <node> cmd declaration                              /**/
%type <node> exp                                          /**/
%token <node> STRING CHAR INT FLOAT                       /**/
%token <node> ID TYPE                                     /**/
%token <node> IN OPPOS OPUNI OPBIN1 OPBIN2 OPBIN3 OPBIN4  /**/
%token <node> OPBIN5 OPBIN6 OPBIN7 OPBIN8 OPASSIGN        /**/
%token <node> '*' '/' '+' '-' '%' '!' '~' '&'             /**/
                                                          /**/
%token IF WHILE FORALL FOR ELSE RETURN                    /**/
%token EMPTY                                              /**/
                                                          /**/
%type arglist argtail parlist partail forargs fortail     /**/
/* ====================================================== /**/

/* ========= Definição de precedencia ======= /**/
%right OPASSIGN                               /**/
%right '?' ':'                                /**/
%left OPBIN8 /* ||        */                  /**/
%left OPBIN7 /* &&        */                  /**/
%left OPBIN6 /* |         */                  /**/
%left OPBIN5 /* ^         */                  /**/
%left OPBIN4 /* &         */                  /**/
%left OPBIN3 /* == !=     */                  /**/
%left OPBIN2 /* > < >= <= */                  /**/
%left OPBIN1 /* << >>     */                  /**/
%left '+' '-'                                 /**/
%left '*' '/' '%'                             /**/
%left IN                                      /**/
%right '!' '~' '&' OPUNI /* + - ++ -- * & */  /**/
%left OPPOS                                   /**/
                                              /**/
%precedence IF                                /**/
%precedence ELSE                              /**/
/* ========================================== /**/

%%

prog: declarations;

declarations: %empty
	| declaration {
		add_child($1, parents->first->value);
	} declarationstail
;

declarationstail: %empty
	| declaration {
		add_child($1, parents->first->value);
	} declarationstail
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
		insert(0, $<node>$, parents);
	} '(' forargs ')' {
		removeAt(0, parents);
	} cmd {
		$$ = $<node>2;
		add_child($7, $$);
	}
	| exp ';' { $$ = $1; }
	| RETURN exp ';' {
		add_child($2, ($$ = create_node(strdup("<return>"))));
	}
	| {
		insert(0, create_node(strdup("<block>")), parents);
		PUSH_CONTEXT;
	} '{' cmds '}' {
		POP_CONTEXT;
		$$ = parents->first->value;
		removeAt(0, parents);
	}
	| ';' {
		$$ = create_node(strdup("<emptycmd>"));
	}
	| declaration
	/* Erros */
	| IF '(' error ')' cmd %prec IF {
		$$ = create_node(strdup("<if>"));
		add_child(create_node(ERR_TOKEN), $$);
		add_child($5, $$);
		ssprintf(syn_errormsg, "Expected condition in 'if' statement");
	}
	| IF '(' error ')' cmd ELSE cmd %prec ELSE {
		$$ = create_node(strdup("<if-else>"));
		add_child(create_node(ERR_TOKEN), $$);
		add_child($5, $$);
		add_child($7, $$);
		ssprintf(syn_errormsg, "Expected condition in 'if-else' statement");
	}
	| WHILE '(' error ')' cmd {
		$$ = create_node(strdup("<while>"));
		add_child(create_node(ERR_TOKEN), $$);
		add_child($5, $$);
		ssprintf(syn_errormsg, "Expected condition in 'while' statement");
	}
	| FORALL '(' error ')' cmd {
		$$ = create_node(strdup("<forall>"));
		add_child(create_node(ERR_TOKEN), $$);
		add_child($5, $$);
		ssprintf(syn_errormsg, "Expected in-expression in 'forall' statement");
	}
	| RETURN error ';' {
		$$ = create_node(strdup("<return>"));
		add_child(create_node(ERR_TOKEN), $$);
		ssprintf(syn_errormsg, "Expected return expression");
	}
;

cmds: %empty
	| cmd {
		add_child($1, parents->first->value);
	} cmdstail
;

cmdstail: %empty
	| cmd {
		add_child($1, parents->first->value);
	} cmdstail
;

declaration: TYPE ID {
		$<node>$ = create_node(strdup("<declr>"));
		add_child($1, $<node>$);
		add_child($2, $<node>$);
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
		insert(0, $<node>$, parents);
	} idlist ';' {
		$$ = $<node>3;
		removeAt(0, parents);
	}
	| TYPE ID '(' {
		$<node>$ = create_node(strdup("<declr_fn>"));
		add_child($1, $<node>$);
		add_child($2, $<node>$);
		ADD_CONTEXT(FUN, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
		PUSH_CONTEXT;

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, $<node>$);
		insert(0, pars, parents); /* É removido dentro de declr_fntail */
	} declr_fntail {
		POP_CONTEXT;
		$$ = $<node>4;
	}
	/* Erros */
	| TYPE idlist {
		$<node>$ = create_node(strdup("<declr>"));
		add_child($1, $<node>$);
		add_child(create_node(ERR_TOKEN), $<node>$);
		insert(0, $<node>$, parents);
	} ';' {
		removeAt(0, parents);
		YYERROR;
	} error {
		$$ = $<node>3;
		ssprintf(
			syn_errormsg,
			"Expected identifier of type '%s'",
			FIRSTCHILD_VALUE($1)
		);
	}
	| TYPE {
		$<node>$ = create_node(strdup("<declr_fn>"));
		add_child($1, $<node>$);
		add_child(create_node(ERR_TOKEN), $<node>$);

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, $<node>$);
		insert(0, pars, parents);
		PUSH_CONTEXT;
	} '(' parlist ')' {
		removeAt(0, parents);
		$<node>$ = $<node>2;
		node_t block = create_node(strdup("<block>"));
		add_child(block, $<node>$);
		insert(0, block, parents);
	} '{' cmds '}' {
		POP_CONTEXT;
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
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
	} cmds '}' {
		removeAt(0, parents);
	}
	/* Erros */
	| error '{' {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);

		add_child(create_node(ERR_TOKEN), parents->first->value);

		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
		ssprintf(syn_errormsg, "Expected a ')'");
	} cmds '}' {
		removeAt(0, parents);
	}
	| parlist ')' error ';' {
		node_t err = create_node(ERR_TOKEN);
		node_t block = create_node(strdup("<block>"));
		add_child(err, block);
		add_child(block, ((node_t) parents->first->value)->parent);

		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, err, parents);
		ssprintf(syn_errormsg, "Expected a '{'");
	} cmds '}' {
		removeAt(0, parents);
	}
;

parlist: %empty
	| TYPE ID {
		$<node>$ = create_node(strdup("<declr>"));
		add_child($1, $<node>$);
		add_child($2, $<node>$);
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
		add_child($<node>$, parents->first->value);
	} partail
	/* Erros */
	| ID { /* Missing type */
		add_child(create_node(ERR_TOKEN), parents->first->value);
		add_child($1, parents->first->value);
		YYERROR;
	} partail error {
		ssprintf(syn_errormsg, "Expected a type for '%s'", FIRSTCHILD_VALUE($1));
	}
	| TYPE { /* Missing id */
		add_child($1, parents->first->value);
		add_child(create_node(ERR_TOKEN), parents->first->value);
		YYERROR;
	} partail error {
		ssprintf(syn_errormsg, "Expected an identifier of type '%s'", FIRSTCHILD_VALUE($1));
	}
;

partail: %empty
	| ',' TYPE ID partail {
		$<node>$ = create_node(strdup("<declr>"));
		add_child($2, $<node>$);
		add_child($3, $<node>$);
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE($3), FIRSTCHILD_VALUE($2));
		add_child($<node>$, parents->first->value);
	}
	/* Erros */
	| TYPE ID partail {
		$<node>$ = create_node(strdup("<declr>"));
		add_child($1, $<node>$);
		add_child($2, $<node>$);
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
		add_child($<node>$, parents->first->value);
		ssprintf(syn_errormsg, "Expected a ','");
	}
;

forargs: TYPE ID '=' exp {
		node_t arg = create_node(strdup("<declr_init>"));
		add_child($1, arg);
		add_child($2, arg);
		add_child($4, arg);

		add_child(arg, parents->first->value);
		insert(0, arg, parents);
	} fordeclrlist { /* TODO: Tem que poder fazer várias declarações sem iniciar */
		removeAt(0, parents);
	} fortail fortail
	| TYPE ID {
		node_t arg = create_node(strdup("<declr>"));
		add_child($1, arg);
		add_child($2, arg);

		add_child(arg, parents->first->value);
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
		add_child(create_node(ERR_TOKEN), parents->first->value);
		ssprintf(syn_errormsg, "Expected an identifier");
	} idlist
;

exp: INT     { add_child($1, ($$ = create_node(strdup("<int>"))));    }
	| FLOAT  { add_child($1, ($$ = create_node(strdup("<float>"))));  }
	| EMPTY  { $$ = create_node(strdup("<empty>"));                   }
	| STRING { add_child($1, ($$ = create_node(strdup("<string>")))); }
	| CHAR   { add_child($1, ($$ = create_node(strdup("<char>"))));   }
	| ID     { $$ = $1; }
	| ID OPPOS {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<oppos>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		$$ = exp;
	}
	| '*' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '+' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '-' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '!' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '~' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '&' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| OPUNI exp           { ADD_UNI_EXP($$, $1, $2);     }
	| exp '*' exp         { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp '/' exp         { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp '%' exp         { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp '+' exp         { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp '-' exp         { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp IN exp          { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp OPBIN1 exp      { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp OPBIN2 exp      { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp OPBIN3 exp      { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp OPBIN4 exp      { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp OPBIN5 exp      { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp OPBIN6 exp      { ADD_BIN_EXP($$, $1, $2, $3); }
	| exp OPBIN7 exp      { ADD_BIN_EXP($$, $1, $2, $3); }
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
		insert(0, $<node>$, parents);
	} fntail {
		$$ = $<node>2;
		removeAt(0, parents);
	}
	| '(' exp ')' { add_child($2, ($$ = create_node(strdup("<exp>")))); }
	/* Erros */
	| exp '*' error    { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp '/' error    { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp '%' error    { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp '+' error    { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp '-' error    { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN1 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN2 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN3 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN4 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN5 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN6 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN7 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| exp OPBIN8 error { ADD_BIN_EXP_ERR($$, $1, $2); }
	| ID OPASSIGN error {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child($2, op);
		add_child($1, exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child(err, exp);
		$$ = exp;
		ssprintf(
			syn_errormsg,
			"Expected expression in '%s %s'",
			FIRSTCHILD_VALUE($1),
			$2->value
			);
	}
;

fntail: '(' arglist ')'
	| '(' arglist error { ssprintf(syn_errormsg, "Expected ')'"); }
;

arglist: %empty
	| exp argtail { add_child($1, parents->first->value); }
;

argtail: %empty
	| ',' exp argtail { add_child($2, parents->first->value); }
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

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsnprintf(target, NAMESIZE, template, ap);
	va_end(ap);
}

void print(node_t node, void *data) {
	printData_t *dataSt = data;
	int *childrenCount = dataSt->childrenCount;

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
	dataSt->val_print(node);
	printf("\n");
}

void print_syntatic(node_t node) {
	printf("%s",
		node->children->size > 0 && node->parent != NULL ?
			TREEFADECOLOR :
			TREEACCENTCOLOR
		);
	printf("%s", (char *) node->value);
	printf("\033[0m");
}

void print_context(node_t node) {
	elem_t it = ((list_t) node->value)->first;
	for (; it != NULL; it = it->next) {
		printf("%s%s", (char *) it->value, it->next != NULL ? ", " : "");
	}
}

void max_level(node_t node, void *data) {
	int *max = (int *) data;
	int l = level(node);
	if (*max < l) *max = l;
}

void free_values(node_t node, void *data) {
	if (strcmp(node->value, ERR_TOKEN) && strcmp(node->value, filename)) {
		free(node->value);
	}
}

void free_context(node_t node, void *data) {
	elem_t it = ((list_t) node->value)->first;
	for (; it != NULL; it = it->next) {
		free(it->value);
	}
	delete_list(node->value);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}

	/** ============= Inicializando valores ================ **/
	yyin = fopen(argv[1], "r");                             /**/
	assert(yyin);                                           /**/
                                                            /**/
	strncpy(filename, argv[1], FILENAMESIZE);               /**/
	extern char *filename_lex;                              /**/
	filename_lex = filename;                                /**/
	root = create_node(filename);                           /**/
	context = create_node(create_list());                   /**/
	current_context = context;                              /**/
	parents = create_list();                                /**/
	int max = 0, *childrenCount = NULL;                     /**/
                                                            /**/
	insert(0, root, parents);                               /**/
	/** ==================================================== **/

	int ret;
	if ((ret = yyparse(&max, childrenCount))) {
		fprintf(stderr, "Unhandled error while parsing\n");
	}

	if (*syn_errormsg) {
		fprintf(stderr, ERR_TEMPLATE, syn_errormsg);
	}

	/** ============== Finalizando valores ================= **/
	removeAt(0, parents);                                   /**/
                                                            /**/
		/* Pega a profundidade da árvore */                 /**/
	depth_pre(max_level, context, &max, NULL, NULL);        /**/
	childrenCount = (int *) calloc(max, sizeof(int));       /**/
		/* Imprime contextos */                             /**/
	printf("Árvore de contextos / Tabela de símbolos\n");   /**/
	printData_t ctx_data = {childrenCount, print_context};  /**/
	depth_pre(print, context, &ctx_data, NULL, NULL);       /**/
	free(childrenCount);                                    /**/
	/* Limpa o contexto */                                  /**/
	depth_pos(free_context, context, NULL, NULL, NULL);     /**/
	delete_node(context);                                   /**/
                                                            /**/
		/* Sublinha o nome do arquivo */                    /**/
	/* sprintf(              */                             /**/
	/*  root->value,         */                             /**/
	/*  "\033[4m%s\033[0m",  */                             /**/
	/*  (char *) root->value */                             /**/
	/* );                    */                             /**/
                                                            /**/
		/* Pega a profundidade da árvore */                 /**/
	depth_pre(max_level, root, &max, NULL, NULL);           /**/
	childrenCount = (int *) calloc(max, sizeof(int));       /**/
		/* Imprime a árvore sintática */                    /**/
	printf("Árvore sintática abstrata\n");                  /**/
	printData_t syn_data = {childrenCount, print_syntatic}; /**/
	depth_pre(print, root, &syn_data, NULL, NULL);          /**/
	free(childrenCount);                                    /**/
		/* Limpa a árvore sintática */                      /**/
	depth_pos(free_values, root, NULL, NULL, NULL);         /**/
	delete_node(root);                                      /**/
	delete_list(parents);                                   /**/
                                                            /**/
		/* Limpa coisas do flex */                          /**/
	fclose(yyin);                                           /**/
	yylex_destroy();                                        /**/
	/** ==================================================== **/

	return ret;
}
