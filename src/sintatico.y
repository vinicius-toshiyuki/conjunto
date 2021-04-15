%define lr.type canonical-lr

/* Parâmetros para a função yyparse() */
%parse-param {int *max} {int *children_count}

%{ /* ================== INÍCIO DO PREFÁCIO ===================== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>
#include <assert.h>
#include <lexico.h>
#include <tree.h>
#include <util.h>

#define NAMESIZE 32768
#define FILENAMESIZE 512

/* ========================= Macros ============================= */
#define FIRSTCHILD_VALUE(NODE) \
	((char *) ((node_t) NODE->children->first->value)->value)

#define ADD_BIN_EXP(RES, EXP1, OP, EXP2) { \
	node_t exp = create_node(TOK_EXP);     \
	node_t op = create_node(TOK_OPBIN);    \
	add_child(OP, op);                     \
	add_child(EXP1, exp);                  \
	add_child(op, exp);                    \
	add_child(EXP2, exp);                  \
	RES = exp;                             \
}

#define ADD_BIN_EXP_ERR(RES, EXP1, OP) {   \
	node_t exp = create_node(TOK_EXP);     \
	node_t op = create_node(TOK_OPBIN);    \
	add_child(OP, op);                     \
	add_child(EXP1, exp);                  \
	add_child(op, exp);                    \
	node_t err = create_node(ERR_TOKEN);   \
	add_child(err, exp);                   \
	RES = exp;                             \
	ssprintf(                              \
		syn_errormsg,                      \
		"Expected expression before '%s'", \
		OP->value                          \
		);                                 \
	HANDLE_ERROR(syn_errormsg);            \
}

#define ADD_UNI_EXP(RES, OP, EXP1) {    \
	node_t exp = create_node(TOK_EXP);  \
	node_t op = create_node(TOK_OPUNI); \
	add_child(OP, op);                  \
	add_child(op, exp);                 \
	add_child(EXP1, exp);               \
	RES = exp;                          \
}

#define UNDEF_ID_ERR(ID) { \
	CTX_sym_t sym = lookup_symbol(ID, current_context); \
	if (sym == NULL) { \
		yyerror(NULL, NULL, NULL); \
		ssprintf( \
			syn_errormsg, \
			"Undefined identifier \"%s\"", \
			ID \
			); \
		HANDLE_ERROR(syn_errormsg); \
	} \
}

#define PUSH_CONTEXT {                            \
	node_t OLD_CONTEXT = current_context;         \
	current_context = create_node(create_list()); \
	add_child(current_context, OLD_CONTEXT);      \
}

#define POP_CONTEXT \
	current_context = current_context->parent;

#define ADD_CONTEXT(SYM_TYPE, ID_CONTEXT, TYPE_CONTEXT) {               \
	if (has_symbol(ID_CONTEXT, current_context->value) != 0) {          \
		int ENTRYTYPE = data_type_code(TYPE_CONTEXT);                   \
		CTX_sym_t SYM = create_symbol(SYM_TYPE, ID_CONTEXT, ENTRYTYPE); \
		append(SYM, current_context->value);                            \
	} else {                                                            \
		yyerror(NULL, NULL, NULL); \
		ssprintf(syn_errormsg, "Redeclaration of \"%s\"", ID_CONTEXT); \
		HANDLE_ERROR(syn_errormsg); \
	}                                                                   \
}

/* ============================================================== */

/* Estrutura para passar argumentos para impressão */
typedef struct {
	int *children_count;
	void (*val_print)(node_t value);
	int only_spaces;
} print_data_t;

/* Assinatura dependente do %parse-param */
int yyerror(int *max, int *children_count, char *s);
int yylex();

void ssprintf(char *target, char *template, ...); /* É a mesma coisa do sprintf()                 */
void print(node_t node, void *data);              /* Imprime um nó de uma árvore                  */
void print_syntatic(node_t value);                /* Imprime o valor de um nó da árvore sintática */
void print_context(node_t value);                 /* Imprime o valor de um nó do contexto         */
void max_level(node_t node, void *data);          /* Obtém a profundidade de uma árvore           */
void free_values(node_t node, void *data);        /* Libera a memória do valor de um nó           */
void free_context(node_t node, void *data);       /* Libera a memória de um context               */
void init_context(node_t node);                   /* Inicia o contexto com funções integradas */

extern int lnum, lcol; /* Vêm do lexico.l */

list_t err_loc;

char filename[FILENAMESIZE + 1]; /* Armazena o nome do arquivo de entrada */
char syn_errormsg[NAMESIZE + 1]; /* Armazena a próxima mensagem de erro */

node_t root;    /* Raiz da árvore sintática */
list_t parents; /* Auxilia na inserção na árvore */

node_t current_context;
node_t context; /* Árvore de contextos */

%}
/* ======================= FIM DO PREFÁCIO ====================== */

%code requires {
#include <tree.h>
#include <context.h>
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
		} declarations
	;

cmd: IF '(' exp ')' cmd %prec IF
		{
			$$ = create_node(TOK_IF);
			add_child($3, $$);
			add_child($5, $$);
		}
	| IF '(' exp ')' cmd ELSE cmd %prec ELSE
		{
			$$ = create_node(TOK_IF_ELSE);
			add_child($3, $$);
			add_child($5, $$);
			add_child($7, $$);
		}
	| WHILE '(' exp ')' cmd
		{
			$$ = create_node(TOK_WHILE);
			add_child($3, $$);
			add_child($5, $$);
		}
	| FORALL '(' exp ')' cmd
		{
			$$ = create_node(TOK_FORALL);
			add_child($3, $$);
			add_child($5, $$);
		}
	| FOR
		{
			$<node>$ = create_node(TOK_FOR);
			insert(0, $<node>$, parents);
		} '(' forargs ')' {
			removeAt(0, parents);
		} cmd {
			$$ = $<node>2;
			add_child($7, $$);
		}
	| exp ';' { $$ = $1; }
	| RETURN exp ';'
		{
			add_child($2, ($$ = create_node(TOK_RETURN)));
		}
	|
		{
			insert(0, create_node(TOK_BLOCK), parents);
			PUSH_CONTEXT;
		} '{' cmds '}' {
			POP_CONTEXT;
			$$ = parents->first->value;
			removeAt(0, parents);
		}
	| ';'
		{
			$$ = create_node(TOK_EMPTYCMD);
		}
	| declaration
	/* Erros */
	| IF '(' error ')' cmd %prec IF
		{
			$$ = create_node(TOK_IF);
			add_child(create_node(ERR_TOKEN), $$);
			add_child($5, $$);
			HANDLE_ERROR("Expected condition in 'if' statement");
		}
	| IF '(' error ')' cmd ELSE cmd %prec ELSE
		{
			$$ = create_node(TOK_IF_ELSE);
			add_child(create_node(ERR_TOKEN), $$);
			add_child($5, $$);
			add_child($7, $$);
			HANDLE_ERROR("Expected condition in 'if-else' statement");
		}
	| WHILE '(' error ')' cmd
		{
			$$ = create_node(TOK_WHILE);
			add_child(create_node(ERR_TOKEN), $$);
			add_child($5, $$);
			HANDLE_ERROR("Expected condition in 'while' statement");
		}
	| FORALL '(' error ')' cmd
		{
			$$ = create_node(TOK_FORALL);
			add_child(create_node(ERR_TOKEN), $$);
			add_child($5, $$);
			HANDLE_ERROR("Expected in-expression in 'forall' statement");
		}
	| RETURN error ';'
		{
			$$ = create_node(TOK_RETURN);
			add_child(create_node(ERR_TOKEN), $$);
			HANDLE_ERROR("Expected return expression");
		}
	;

cmds: %empty
	| cmd
		{
			add_child($1, parents->first->value);
		} cmdstail
	;

cmdstail: %empty
	| cmd
		{
			add_child($1, parents->first->value);
		} cmdstail
	;

declaration: TYPE ID
		{
			$<node>$ = create_node(TOK_DECLR);
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			ADD_CONTEXT(CTX_VAR, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
			insert(0, $<node>$, parents);
		} idlist ';' {
			$$ = $<node>3;
			removeAt(0, parents);
		}
	| TYPE ID '('
		{
			$<node>$ = create_node(strdup("<declr_fn>"));
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			ADD_CONTEXT(CTX_FUN, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
			PUSH_CONTEXT;

			node_t pars = create_node(TOK_PARLIST);
			add_child(pars, $<node>$);
			insert(0, pars, parents); /* É removido dentro de declr_fntail */
		} declr_fntail {
			POP_CONTEXT;
			$$ = $<node>4;
		}
	/* Erros */
	| TYPE idlist
		{
			$<node>$ = create_node(TOK_DECLR);
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
			HANDLE_ERROR(syn_errormsg);
		}
	| TYPE
		{
			$<node>$ = create_node(strdup("<declr_fn>"));
			add_child($1, $<node>$);
			add_child(create_node(ERR_TOKEN), $<node>$);

			node_t pars = create_node(TOK_PARLIST);
			add_child(pars, $<node>$);
			insert(0, pars, parents);
			PUSH_CONTEXT;
		} '(' parlist ')' {
			removeAt(0, parents);
			$<node>$ = $<node>2;
			node_t block = create_node(TOK_BLOCK);
			add_child(block, $<node>$);
			insert(0, block, parents);
		} '{' cmds '}' {
			POP_CONTEXT;
			removeAt(0, parents);
			YYERROR;
		} error {
			$$ = $<node>6;
			ssprintf(
				syn_errormsg,
				"Expected identifier of type '%s' in function declaration",
				$1->value
				);
			HANDLE_ERROR(syn_errormsg);
		}
	;

declr_fntail: parlist ')' '{'
		{
			node_t block = create_node(TOK_BLOCK);
			add_child(block, ((node_t) parents->first->value)->parent);
			removeAt(0, parents); /* Inserido no que vem antes */
			insert(0, block, parents);
		} cmds '}' {
			removeAt(0, parents);
		}
	/* Erros */
	| error '{'
		{
			node_t block = create_node(TOK_BLOCK);
			add_child(block, ((node_t) parents->first->value)->parent);

			add_child(create_node(ERR_TOKEN), parents->first->value);

			removeAt(0, parents); /* Inserido no que vem antes */
			insert(0, block, parents);
			HANDLE_ERROR("Expected a ')'");
		} cmds '}' {
			removeAt(0, parents);
		}
	| parlist ')' error ';'
		{
			node_t err = create_node(ERR_TOKEN);
			node_t block = create_node(TOK_BLOCK);
			add_child(err, block);
			add_child(block, ((node_t) parents->first->value)->parent);

			removeAt(0, parents); /* Inserido no que vem antes */
			insert(0, err, parents);
			HANDLE_ERROR("Expected a '{'");
		} cmds '}' {
			removeAt(0, parents);
		}
	;

parlist: %empty
	| TYPE ID
		{
			$<node>$ = create_node(TOK_DECLR);
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			ADD_CONTEXT(CTX_VAR, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
			add_child($<node>$, parents->first->value);
		} partail
	/* Erros */
	| ID
		{ /* Missing type */
			add_child(create_node(ERR_TOKEN), parents->first->value);
			add_child($1, parents->first->value);
			YYERROR;
		} partail error {
			ssprintf(syn_errormsg, "Expected a type for '%s'", FIRSTCHILD_VALUE($1));
			HANDLE_ERROR(syn_errormsg);
		}
	| TYPE
		{ /* Missing id */
			add_child($1, parents->first->value);
			add_child(create_node(ERR_TOKEN), parents->first->value);
			YYERROR;
		} partail error {
			ssprintf(syn_errormsg, "Expected an identifier of type '%s'", FIRSTCHILD_VALUE($1));
			HANDLE_ERROR(syn_errormsg);
		}
	;

partail: %empty
	| ',' TYPE ID partail
		{
			$<node>$ = create_node(TOK_DECLR);
			add_child($2, $<node>$);
			add_child($3, $<node>$);
			ADD_CONTEXT(CTX_VAR, FIRSTCHILD_VALUE($3), FIRSTCHILD_VALUE($2));
			add_child($<node>$, parents->first->value);
		}
	/* Erros */
	| TYPE ID partail
		{
			$<node>$ = create_node(TOK_DECLR);
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			ADD_CONTEXT(CTX_VAR, FIRSTCHILD_VALUE($2), FIRSTCHILD_VALUE($1));
			add_child($<node>$, parents->first->value);
			HANDLE_ERROR("Expected a ','");
		}
	;

forargs: TYPE ID '=' exp
		{
			node_t arg = create_node(strdup("<declr_init>"));
			add_child($1, arg);
			add_child($2, arg);
			add_child($4, arg);

			add_child(arg, parents->first->value);
			insert(0, arg, parents);
		} fordeclrlist { /* TODO: Tem que poder fazer várias declarações sem iniciar */
			removeAt(0, parents);
		} fortail fortail
	| TYPE ID
		{
			node_t arg = create_node(TOK_DECLR);
			add_child($1, arg);
			add_child($2, arg);

			add_child(arg, parents->first->value);
			insert(0, arg, parents);
		} idlist {
			removeAt(0, parents);
		} fortail fortail
	| exp
		{
			add_child($1, parents->first->value);
		} fortail fortail
	| fortail fortail
		{
			node_t exp = create_node(TOK_EMPTYEXP);
			exp->parent = parents->first->value;
			insert(0, exp, parents->first->value);
		}
	;

fordeclrlist: %empty
	| ',' ID '=' exp fordeclrlist
		{
			add_child($2, parents->first->value);
			add_child($4, parents->first->value);
		}
	;

fortail: ';' exp
		{
			add_child($2, parents->first->value);
		}
	| ';'
		{
			add_child(create_node(TOK_EMPTYEXP), parents->first->value);
		}
	;

idlist: %empty
	| ',' ID
		{
			add_child($2, parents->first->value);
		} idlist
	| ',' error
		{
			add_child(create_node(ERR_TOKEN), parents->first->value);
			HANDLE_ERROR("Expected an identifier");
		} idlist
	;

exp: INT     { add_child($1, ($$ = create_node(TOK_INT)));    }
	| FLOAT  { add_child($1, ($$ = create_node(TOK_FLOAT)));  }
	| EMPTY  { $$ = create_node(TOK_EMPTY);                   }
	| STRING { add_child($1, ($$ = create_node(TOK_STRING))); }
	| CHAR   { add_child($1, ($$ = create_node(TOK_CHAR)));   }
	| ID
		{
			$$ = $1;
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
		}
	| ID OPPOS
		{
			node_t exp = create_node(TOK_EXP);
			node_t op = create_node(TOK_OPPOS);
			add_child($2, op);
			add_child($1, exp);
			add_child(op, exp);
			$$ = exp;
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
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
	| exp '?' exp ':' exp
		{
			node_t exp = create_node(TOK_EXP);
			node_t op1 = create_node(TOK_OPTER);
			node_t op2 = create_node(TOK_OPTER);
			add_child($<node>2, op1);
			add_child($<node>4, op2);
			add_child($1, exp);
			add_child(op1, exp);
			add_child($3, exp);
			add_child(op2, exp);
			add_child($5, exp);
			$$ = exp;
		}
	| ID OPASSIGN exp
		{
			node_t exp = create_node(TOK_EXP);
			node_t op = create_node(TOK_OPASSIGN);
			add_child($2, op);
			add_child($1, exp);
			add_child(op, exp);
			add_child($3, exp);
			$$ = exp;
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
		}
	| ID
		{
			$<node>$ = create_node(TOK_FN);
			add_child($1, $<node>$);
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
			insert(0, $<node>$, parents);
		} fntail {
			$$ = $<node>2;
			removeAt(0, parents);
		}
	| '(' exp ')' { add_child($2, ($$ = create_node(TOK_EXP))); }
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
	| ID OPASSIGN error
		{
			node_t exp = create_node(TOK_EXP);
			node_t op = create_node(TOK_OPASSIGN);
			add_child($2, op);
			add_child($1, exp);
			add_child(op, exp);
			node_t err = create_node(ERR_TOKEN);
			add_child(err, exp);
			$$ = exp;
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
			ssprintf(
				syn_errormsg,
				"Expected expression in '%s %s'",
				FIRSTCHILD_VALUE($1),
				$2->value
				);
			HANDLE_ERROR(syn_errormsg);
		}
	;

fntail: '(' arglist ')'
	| '(' arglist error { HANDLE_ERROR("Expected ')'"); }
	;

arglist: %empty
	| exp argtail { add_child($1, parents->first->value); }
	;

argtail: %empty
	| ',' exp argtail { add_child($2, parents->first->value); }
	;

%%

int yyerror(int *max, int *children_count, char *s) {
	err_loc_t *loc = (err_loc_t *) malloc(sizeof(err_loc_t));
	loc->errlnum = lnum;
	loc->errlcol = lcol;
	prepend(loc, err_loc);
	return 0;
}

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsnprintf(target, NAMESIZE, template, ap);
	va_end(ap);
}

void print(node_t node, void *data) {
	/* TODO: talvez tenha ficado muito bagunçado com only_spaces? */
	print_data_t *data_st = data;
	int *children_count = data_st->children_count;

	int l = level(node);
	int is_last = 1;

	if (!data_st->only_spaces) {
		children_count[l - 1] = node->children->size;

		/* Checa se este nó é o último filho */
		if (node->parent != NULL) {
			int idx = indexOf(node, node->parent->children);
			is_last = idx < 0 || idx == node->parent->children->size - 1;
		}
		if (is_last) {
			/* Desabilita a impressão de TREECHILD */
			children_count[l - 1] = 0;
		}

		/* Imprime os espaços e TREECHILD necessários */
		for (int i = 0; i < l - 1; i++) {
			printf("%s ", children_count[i] ? TREECHILD : " ");
		}
		/* Se não é o nó raiz */
		if (l > 1) {
			printf( /* NOTE: 6 caracteres no total */
				"%s" TREEBRANCH "%s" TREEBRANCH TREELEAF " ",
				is_last ? TREECHILDLAST : TREECHILDMID,
				node->children->size ? TREECHILDFIRST : TREEBRANCH
				);
		}

		data_st->val_print(node);
		printf("\n");
	} else {
		for (int i = 0; i < l; i++) {
			printf("%s ", children_count[i] ? TREECHILD : " ");
		}
		/* NOTE: 4 caracteres */
		printf(
			"%s " TREEEXTENSION " ",
			node->children->size ? TREECHILD : " "
			);
	}
}

void print_syntatic(node_t node) {
	printf("%s",
		node->children->size > 0 && node->parent != NULL ?
			TREEFADECOLOR :
			TREEACCENTCOLOR
		);

	printf(
		"%s%s" PARSER_CLEARCOLOR,
		node->parent == NULL ? "\033[4m" : "",
		(char *) node->value
		);
	printf("\033[0m");
}

void print_context(node_t node) {
	int l = level(node);
	int *children_count = (int *) calloc(l, sizeof(int));

	node_t traveler = node;
	for (int i = 0; i < l; i++) {
		children_count[l - i - 1] =
			traveler->parent != NULL &&
			traveler != traveler->parent->children->last->value;
		traveler = traveler->parent;
	}

	print_data_t data = {children_count, NULL, 1};
	elem_t it = ((list_t) node->value)->first;
	if (it == NULL) {
		printf(TREEFADECOLOR "(empty)" PARSER_CLEARCOLOR);
	} else {
		for (; it != NULL; it = it->next) {
			CTX_sym_t sym = it->value;
			printf(
				"%s%s: (%s) \"" TREEACCENTCOLOR "%s" PARSER_CLEARCOLOR "\"",
				node->parent == NULL && it == ((list_t)node->value)->first?
					TREEBRANCH TREEBRANCH TREECHILDFIRST TREEBRANCH  TREELEAF " " :
					"",
				type_string(sym->type),
				data_type_string(sym->data_type),
				sym->id
				);
			if (it->next != NULL) {
				printf("\n");
				print(node, &data);
			}
		}
	}
	free(children_count);
}

void max_level(node_t node, void *data) {
	int *max = (int *) data;
	int l = level(node);
	if (*max < l) *max = l;
}

void free_values(node_t node, void *data) {
	if (!IS_TOK(node->value) && strcmp(node->value, filename)) {
		free(node->value);
	}
}

void free_context(node_t node, void *data) {
	MAP({
		delete_symbol(MAP_val);
	}, node->value);
	delete_list(node->value);
}

void init_context(node_t node) {
	/*
	int write(char *message)
	int writeln(char *message)
	int read(T output)
	int is_set(elem el)
	set add(inexp exp)
	set remove(inexp exp)
	elem exists(inexp exp)
	*/
	CTX_sym_t write   = create_symbol(CTX_FUN, "write"  , CTX_INT);
	CTX_sym_t writeln = create_symbol(CTX_FUN, "writeln", CTX_INT);
	CTX_sym_t read    = create_symbol(CTX_FUN, "read"   , CTX_INT);
	CTX_sym_t is_set  = create_symbol(CTX_FUN, "is_set" , CTX_INT);
	CTX_sym_t add     = create_symbol(CTX_FUN, "add"    , CTX_SET);
	CTX_sym_t remove  = create_symbol(CTX_FUN, "remove" , CTX_SET);
	CTX_sym_t exists  = create_symbol(CTX_FUN, "exists" , CTX_ELEM);
	append(write  , node->value);
	append(writeln, node->value);
	append(read   , node->value);
	append(is_set , node->value);
	append(add    , node->value);
	append(remove , node->value);
	append(exists , node->value);
}

int main(int argc, char **argv) {
	int show_context = 1, show_syntatic_tree = 1;
	char c, *farg = NULL;
	while ((c = getopt(argc, argv, "CSh")) != -1) {
		switch (c) {
		case 'C':
			show_context = 0;
			break;
		case 'S':
			show_syntatic_tree = 0;
			break;
		case 'h':
			printf("%s [OPTIONS] FILE [OPTIONS]\n", argv[0]);
			printf("\t-C\tinibe a impressão da árvore de contexto\n");
			printf("\t-S\tinibe a impressão da árvore sintática de contexto\n");
			printf("\t-h\timprime esta ajuda e sai\n");
			exit(EXIT_SUCCESS);
		case '?':
			if (isprint(optopt)) {
				fprintf(stderr, "Unknown option `-%c`.\n", optopt);
			} else {
				fprintf(stderr, "Unknown option character `\\x%x`.\n", optopt);
			}
		default:
			exit(EXIT_FAILURE);
		}
	}

	farg = argv[optind];
	if (farg == NULL) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}

	/** ============= Inicializando valores ================ **/
	yyin = fopen(farg, "r");                                /**/
	assert(yyin);                                           /**/
                                                            /**/
	strncpy(filename, farg, FILENAMESIZE);                  /**/
	extern char *filename_lex;                              /**/
	filename_lex = filename;                                /**/
	root = create_node(filename);                           /**/
	context = create_node(create_list());                   /**/
	current_context = context;                              /**/
	init_context(context);                                  /**/
	parents = create_list();                                /**/
	err_loc = create_list();                                /**/
	int max = 0, *children_count = NULL;                    /**/
                                                            /**/
	insert(0, root, parents);                               /**/
	/** ==================================================== **/

	int ret;
	if ((ret = yyparse(&max, children_count))) {
		fprintf(stderr, "Unhandled error while parsing\n");
	}

	/** ============== Finalizando valores ================= **/
	removeAt(0, parents);                                   /**/
                                                            /**/
	if (show_context) {                                     /**/
			/* Pega a profundidade da árvore */             /**/
		depth_pre(max_level, context, &max, NULL, NULL);    /**/
		children_count = (int *) calloc(max, sizeof(int));  /**/
			/* Imprime contextos */                         /**/
		printf(                                             /**/
			SEPARATOR                                       /**/
			" Árvore de contextos / Tabela de símbolos "    /**/
			SEPARATOR                                       /**/
			"\n"                                            /**/
			);                                              /**/
		print_data_t ctx_data = {                           /**/
			children_count,                                 /**/
			print_context,                                  /**/
			0                                               /**/
			};                                              /**/
		depth_pre(print, context, &ctx_data, NULL, NULL);   /**/
		free(children_count);                               /**/
	}                                                       /**/
	/* Limpa o contexto */                                  /**/
	depth_pos(free_context, context, NULL, NULL, NULL);     /**/
	delete_node(context);                                   /**/
                                                            /**/
	if (show_syntatic_tree) {                               /**/
			/* Pega a profundidade da árvore */             /**/
		depth_pre(max_level, root, &max, NULL, NULL);       /**/
		children_count = (int *) calloc(max, sizeof(int));  /**/
			/* Imprime a árvore sintática */                /**/
		printf(                                             /**/
			SEPARATOR                                       /**/
			" Árvore sintática abstrata "                   /**/
			SEPARATOR "\n"                                  /**/
			);                                              /**/
		print_data_t syn_data = {                           /**/
			children_count,                                 /**/
			print_syntatic,                                 /**/
			0                                               /**/
			};                                              /**/
		depth_pre(print, root, &syn_data, NULL, NULL);      /**/
		free(children_count);                               /**/
	}                                                       /**/
		/* Limpa a árvore sintática */                      /**/
	depth_pos(free_values, root, NULL, NULL, NULL);         /**/
	delete_node(root);                                      /**/
	delete_list(parents);                                   /**/
                                                            /**/
		/* Limpa a lista de erros */                        /**/
	for_each(free_list, err_loc);                           /**/
	delete_list(err_loc);                                   /**/
                                                            /**/
		/* Limpa coisas do flex */                          /**/
	fclose(yyin);                                           /**/
	yylex_destroy();                                        /**/
	/** ==================================================== **/

	return ret;
}
