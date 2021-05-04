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

/* ========================= Macros ============================= */
#define FIRSTCHILD_VALUE(NODE) \
	((char *) ((node_t) ((node_t)NODE)->children->first->value)->value)

#define ADD_BIN_EXP(RES, EXP1, OP, EXP2) {                           \
	node_t exp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP)); \
	node_t op = create_node(create_syn_val(SYN_TAG, TOK_OPBIN));     \
	add_child(OP, op);                                               \
	add_child(EXP1, exp);                                            \
	add_child(op, exp);                                              \
	add_child(EXP2, exp);                                            \
	eval_exp_type(exp);                                              \
	RES = exp;                                                       \
}

#define ADD_BIN_EXP_ERR(RES, EXP1, OP) {                             \
	node_t exp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP)); \
	node_t op = create_node(create_syn_val(SYN_TAG, TOK_OPBIN));     \
	add_child(OP, op);                                               \
	add_child(EXP1, exp);                                            \
	add_child(op, exp);                                              \
	node_t err = create_node(create_syn_val(SYN_TAG, ERR_TOKEN));    \
	add_child(err, exp);                                             \
	RES = exp;                                                       \
	ssprintf(                                                        \
		syn_errormsg,                                                \
		"Expected expression before '%s'",                           \
		SYN_OP(OP->value)->name                                      \
		);                                                           \
	HANDLE_ERROR(syn_errormsg);                                      \
}

#define ADD_UNI_EXP(RES, OP, EXP1) {                                 \
	node_t exp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP)); \
	node_t op = create_node(create_syn_val(SYN_TAG, TOK_OPUNI));     \
	add_child(OP, op);                                               \
	add_child(op, exp);                                              \
	add_child(EXP1, exp);                                            \
	eval_exp_type(exp);                                              \
	RES = exp;                                                       \
}

#define ADD_POS_EXP(RES, OP, EXP1) {                                 \
	node_t exp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP)); \
	node_t op = create_node(create_syn_val(SYN_TAG, TOK_OPPOS));     \
	SYN_op_t syn_op = OP->value;                                     \
	init_syn_op(syn_op->op_type + 5, syn_op);                        \
	add_child(OP, op);                                               \
	add_child(op, exp);                                              \
	add_child(EXP1, exp);                                            \
	eval_exp_type(exp);                                              \
	RES = exp;                                                       \
}

#define UNDEF_ID_ERR(ID) {                                             \
	CTX_sym_t sym = lookup_symbol(SYN_EXP(ID)->name, current_context); \
	if (sym == NULL) {                                                 \
		yyerror(NULL, NULL, NULL);                                     \
		ssprintf(                                                      \
			syn_errormsg,                                              \
			"Undefined identifier \"%s\"",                             \
			SYN_EXP(ID)->name                                          \
			);                                                         \
		HANDLE_ERROR(syn_errormsg);                                    \
	}                                                                  \
}

#define PUSH_CONTEXT {                            \
	node_t OLD_CONTEXT = current_context;         \
	current_context = create_node(create_list()); \
	add_child(current_context, OLD_CONTEXT);      \
}

#define POP_CONTEXT \
	current_context = current_context->parent;

#define ADD_CONTEXT(SYM_TYPE, ID_CONTEXT, TYPE_CONTEXT) {           \
	char *TYPE_NAME = TYPE_CONTEXT;                                 \
	char *ID_NAME = ID_CONTEXT;                                     \
	CTX_sym_t MAYBE_FUN = lookup_symbol(ID_NAME, context);          \
	if (has_symbol(ID_NAME, current_context->value) != 0 &&         \
		(MAYBE_FUN == NULL || MAYBE_FUN->type != CTX_FUN)) {        \
		int ENTRYTYPE = data_type_code(TYPE_NAME);                  \
		CTX_sym_t SYM = create_symbol(                              \
			SYM_TYPE,                                               \
			ID_NAME,                                                \
			ENTRYTYPE,                                              \
			lnum,                                                   \
			lcol                                                    \
			);                                                      \
		append(SYM, current_context->value);                        \
	} else {                                                        \
		yyerror(NULL, NULL, NULL);                                  \
		ssprintf(syn_errormsg, "Redeclaration of \"%s\"", ID_NAME); \
		HANDLE_ERROR(syn_errormsg);                                 \
	}                                                               \
}

/* ============================================================== */

/* Estrutura para passar argumentos para impressão */
typedef struct {
	int *children_count;
	void (*val_print)(node_t value);
	int only_spaces;
	int detailed;
} print_data_t;

/* Assinatura dependente do %parse-param */
int yyerror(int *max, int *children_count, char *s);
int yylex();

void ssprintf(char *target, char *template, ...);   /* É a mesma coisa do sprintf()                    */
int validate_breaks(node_t node, void *data);       /* Checa se os breaks estão dentro de loops        */
int print(node_t node, void *data);                 /* Imprime um nó de uma árvore                     */
void print_syntatic(node_t value);                  /* Imprime o valor de um nó da árvore sintática    */
void print_context(node_t value);                   /* Imprime o valor de um nó do contexto            */
int max_level(node_t node, void *data);             /* Obtém a profundidade de uma árvore              */
int create_context_table(node_t node, void *data);  /* Popula um set com os símbolos do contexto       */
int free_values(node_t node, void *data);           /* Libera a memória do valor de um nó              */
int free_context(node_t node, void *data);          /* Libera a memória de um context (não o contexto) */
void init_context(node_t node);                     /* Inicia o contexto com funções integradas        */

extern int lnum, lcol; /* Vêm do lexico.l */

list_t err_loc;

char filename[FILENAMESIZE + 1]; /* Armazena o nome do arquivo de entrada */
char syn_errormsg[NAMESIZE + 1]; /* Armazena a próxima mensagem de erro */

node_t root;    /* Raiz da árvore sintática */
list_t parents; /* Auxilia na inserção na árvore */

node_t current_context;
node_t context; /* Árvore de contextos */

/**
 * Indica se um erro foi encontrado durante a
 * construção da árvore sintática e de contextos
 */
int got_error = 0;

%}
/* ======================= FIM DO PREFÁCIO ====================== */

%code requires {
#include <tree.h>
#include <context.h>
#include <syntatic_node.h>
#include <eval.h>
#include <set.h>
#include <translation.h>
}

// %define api.value.type { node_t }
%union {
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
%token IF WHILE FORALL FOR BREAK ELSE RETURN              /**/
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

prog: declarations {
		depth_pre(validate_breaks, parents->first->value, NULL, NULL, NULL);
		CTX_sym_t main_sym = lookup_symbol("main", context);
		if (main_sym == NULL || main_sym->type != CTX_FUN) {
			yyerror(NULL, NULL, NULL);
			sprintf(
				syn_errormsg,
				"Program entry point \"main\" function not declared"
				);
			HANDLE_ERROR(syn_errormsg);
		} else {
			if (main_sym->data_type != CTX_INT) {
				yyerror(NULL, NULL, NULL);
				sprintf(
					syn_errormsg,
					"Invalid return data type \"%s\" for \"main\""
					" function (must be int)",
					data_type_string(main_sym->data_type)
					);
				HANDLE_ERROR(syn_errormsg);
			}
			if (CTX_FUN(main_sym)->params != NULL &&
				CTX_FUN(main_sym)->params->size > 0) {
				yyerror(NULL, NULL, NULL);
				sprintf(
					syn_errormsg,
					"Invalid parameters list size for \"main\" function"
					" (found %lu, must be 0)",
					CTX_FUN(main_sym)->params->size
					);
				HANDLE_ERROR(syn_errormsg);
			}
		}
	};

declarations: %empty
	| declaration {
			add_child($1, parents->first->value);
		} declarations
	;

cmd: IF '(' exp ')' cmd %prec IF
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_IF));
			add_child($3, $$);
			add_child($5, $$);
		}
	| IF '(' exp ')' cmd ELSE cmd %prec ELSE
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_IF_ELSE));
			add_child($3, $$);
			add_child($5, $$);
			add_child($7, $$);
		}
	| WHILE '(' exp ')' cmd
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_WHILE));
			add_child($3, $$);
			add_child($5, $$);
		}
	| FORALL '(' exp ')' cmd
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_FORALL));
			add_child($3, $$);
			add_child($5, $$);
		}
	| FOR
		{
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_FOR));
			prepend($<node>$, parents);
		} '(' forargs ')' {
			removeAt(0, parents);
		} cmd {
			$$ = $<node>2;
			add_child($7, $$);
		}
	| exp ';' { $$ = $1; }
	| BREAK ';'
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_BREAK));
		}
	| RETURN exp ';'
		{
			add_child($2, ($$ = create_node(create_syn_val(SYN_TAG, TOK_RETURN))));
		}
	|
		{
			insert(0, create_node(create_syn_val(SYN_TAG, TOK_BLOCK)), parents);
			PUSH_CONTEXT;
		} '{' cmds '}' {
			POP_CONTEXT;
			$$ = parents->first->value;
			removeAt(0, parents);
		}
	| ';'
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_EMPTYCMD));
		}
	| declaration
	/* Erros */
	| IF '(' error ')' cmd %prec IF
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_IF));
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), $$);
			add_child($5, $$);
			HANDLE_ERROR("Expected condition in 'if' statement");
		}
	| IF '(' error ')' cmd ELSE cmd %prec ELSE
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_IF_ELSE));
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), $$);
			add_child($5, $$);
			add_child($7, $$);
			HANDLE_ERROR("Expected condition in 'if-else' statement");
		}
	| WHILE '(' error ')' cmd
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_WHILE));
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), $$);
			add_child($5, $$);
			HANDLE_ERROR("Expected condition in 'while' statement");
		}
	| FORALL '(' error ')' cmd
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_FORALL));
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), $$);
			add_child($5, $$);
			HANDLE_ERROR("Expected in-expression in 'forall' statement");
		}
	| RETURN error ';'
		{
			$$ = create_node(create_syn_val(SYN_TAG, TOK_RETURN));
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), $$);
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
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_DECLR));
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			ADD_CONTEXT(CTX_VAR, SYN_EXP(FIRSTCHILD_VALUE($2))->name, SYN_TYPE(FIRSTCHILD_VALUE($1))->name);
			insert(0, $<node>$, parents);
		} idlist ';' {
			$$ = $<node>3;
			removeAt(0, parents);
		}
	| TYPE ID '('
		{
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_DECLR_FN));
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			if (current_context == context) {
				ADD_CONTEXT(CTX_FUN, SYN_EXP(FIRSTCHILD_VALUE($2))->name, SYN_TYPE(FIRSTCHILD_VALUE($1))->name);
				CTX_sym_t fun = lookup_symbol(SYN_EXP(child_at(0, $2)->value)->name, current_context);
				PUSH_CONTEXT;
				CTX_FUN(fun)->context = current_context;
			} else {
				yyerror(NULL, NULL, NULL);
				sprintf(
					syn_errormsg,
					"Invalid function declaration of \"%s\" not in global context",
					SYN_EXP(FIRSTCHILD_VALUE($2))->name
					);
				HANDLE_ERROR(syn_errormsg);
			}

			node_t pars = create_node(create_syn_val(SYN_TAG, TOK_PARLIST));
			add_child(pars, $<node>$);
			insert(0, pars, parents); /* É removido dentro de declr_fntail */
		} declr_fntail {
			if (current_context->parent == context) {
				POP_CONTEXT;
			}
			$$ = $<node>4;
		}
	/* Erros */
	| TYPE idlist
		{
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_DECLR));
			add_child($1, $<node>$);
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), $<node>$);
			insert(0, $<node>$, parents);
		} ';' {
			removeAt(0, parents);
			YYERROR;
		} error {
			$$ = $<node>3;
			ssprintf(
				syn_errormsg,
				"Expected identifier of type '%s'",
				SYN_TYPE(FIRSTCHILD_VALUE($1))->name
			);
			HANDLE_ERROR(syn_errormsg);
		}
	| TYPE
		{
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_DECLR_FN));
			add_child($1, $<node>$);
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), $<node>$);

			node_t pars = create_node(create_syn_val(SYN_TAG, TOK_PARLIST));
			add_child(pars, $<node>$);
			insert(0, pars, parents);
			PUSH_CONTEXT;
		} '(' parlist ')' {
			removeAt(0, parents);
			$<node>$ = $<node>2;
			node_t block = create_node(create_syn_val(SYN_TAG, TOK_BLOCK));
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
				SYN_TYPE($1->value)->name
				);
			HANDLE_ERROR(syn_errormsg);
		}
	;

declr_fntail: parlist ')' '{'
		{
			node_t block = create_node(create_syn_val(SYN_TAG, TOK_BLOCK));
			add_child(block, ((node_t) parents->first->value)->parent);
			removeAt(0, parents); /* Inserido no que vem antes */
			insert(0, block, parents);
		} cmds '}' {
			node_t block = parents->first->value;
			char *fun_type = SYN_VALUE(child_at(0, child_at(0, block->parent))->value)->name;
			char *fun_name = SYN_VALUE(child_at(0, child_at(1, block->parent))->value)->name;
			node_t return_node = NULL;
			MAP(if (strcmp(SYN_VALUE(((node_t)MAP_val)->value)->name, TOK_RETURN) == 0) {
				return_node = MAP_val;
				int ret_type = eval_exp_type(child_at(0, return_node));
				int fun_type_code = data_type_code(fun_type);
				if (!can_cast(ret_type, fun_type_code)) {
					yyerror(NULL, NULL, NULL);
					sprintf(
						syn_errormsg,
						"Can not cast type %s to %s",
						data_type_string(ret_type),
						fun_type
						);
					HANDLE_ERROR(syn_errormsg);
				} else {
					cast_to(fun_type_code, return_node);
				}
			}, block->children);
			
			if (return_node == NULL) {
				yyerror(NULL, NULL, NULL);
				sprintf(
					syn_errormsg,
					"Function \"%s\" declaration ended without a return",
					fun_name
					);
				HANDLE_ERROR(syn_errormsg);
			}
			removeAt(0, parents);
		}
	/* Erros */
	| error '{'
		{
			node_t block = create_node(create_syn_val(SYN_TAG, TOK_BLOCK));
			add_child(block, ((node_t) parents->first->value)->parent);

			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), parents->first->value);

			removeAt(0, parents); /* Inserido no que vem antes */
			insert(0, block, parents);
			HANDLE_ERROR("Expected a ')'");
		} cmds '}' {
			removeAt(0, parents);
		}
	| parlist ')' error ';'
		{
			node_t err = create_node(create_syn_val(SYN_TAG, ERR_TOKEN));
			node_t block = create_node(create_syn_val(SYN_TAG, TOK_BLOCK));
			add_child(err, block);
			add_child(block, parents->first->value);

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
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_DECLR));
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			ADD_CONTEXT(CTX_VAR, SYN_EXP(FIRSTCHILD_VALUE($2))->name, SYN_TYPE(FIRSTCHILD_VALUE($1))->name);

			char *fun_name = SYN_VALUE(
				FIRSTCHILD_VALUE(
				((node_t)(parents->first->value))->parent->children->first->next->value)
				)->name;
			CTX_sym_t fun = lookup_symbol(fun_name, current_context);

			CTX_sym_t par = lookup_symbol(SYN_EXP(FIRSTCHILD_VALUE($2))->name, current_context);
			if (par != NULL && fun != NULL) {
				if (CTX_FUN(fun)->params == NULL) {
					CTX_FUN(fun)->params = create_list();
				}
				append(par, CTX_FUN(fun)->params);
			}

			add_child($<node>$, parents->first->value);
		} partail
	/* Erros */
	| ID
		{ /* Missing type */
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), parents->first->value);
			add_child($1, parents->first->value);
			YYERROR;
		} partail error {
			ssprintf(syn_errormsg, "Expected a type for '%s'", SYN_EXP(FIRSTCHILD_VALUE($1))->name);
			HANDLE_ERROR(syn_errormsg);
		}
	| TYPE
		{ /* Missing id */
			add_child($1, parents->first->value);
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), parents->first->value);
			YYERROR;
		} partail error {
			ssprintf(syn_errormsg, "Expected an identifier of type '%s'", SYN_TYPE(FIRSTCHILD_VALUE($1))->name);
			HANDLE_ERROR(syn_errormsg);
		}
	;

partail: %empty
	| ',' TYPE ID
		{
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_DECLR));
			add_child($2, $<node>$);
			add_child($3, $<node>$);
			ADD_CONTEXT(CTX_VAR, SYN_EXP(FIRSTCHILD_VALUE($3))->name, SYN_TYPE(FIRSTCHILD_VALUE($2))->name);

			char *fun_name = SYN_VALUE(FIRSTCHILD_VALUE(((node_t)(parents->first->value))->parent->children->first->next->value))->name;
			CTX_sym_t fun = lookup_symbol(fun_name, current_context);

			CTX_sym_t par = lookup_symbol(SYN_EXP(FIRSTCHILD_VALUE($3))->name, current_context);
			if (par != NULL && fun != NULL) {
				if (CTX_FUN(fun)->params == NULL) {
					CTX_FUN(fun)->params = create_list();
				}
				append(par, CTX_FUN(fun)->params);
			}

			add_child($<node>$, parents->first->value);
		} partail
	/* Erros */
	| TYPE ID partail
		{
			$<node>$ = create_node(create_syn_val(SYN_TAG, TOK_DECLR));
			add_child($1, $<node>$);
			add_child($2, $<node>$);
			ADD_CONTEXT(CTX_VAR, SYN_EXP(FIRSTCHILD_VALUE($2))->name, SYN_TYPE(FIRSTCHILD_VALUE($1))->name);
			add_child($<node>$, parents->first->value);
			HANDLE_ERROR("Expected a ','");
		}
	;

forargs: 
	// TYPE ID '=' exp
	// 	{
	// 		node_t arg = create_node(create_syn_val(SYN_TAG, TOK_EXP));
	// 		add_child($1, arg);
	// 		add_child($2, arg);
	// 		add_child($4, arg);

	// 		ADD_CONTEXT(CTX_VAR, SYN_EXP(FIRSTCHILD_VALUE($2))->name, SYN_TYPE(FIRSTCHILD_VALUE($1))->name);

	// 		eval_exp_type(arg);
	// 		SYN_VALUE(arg->value)->name = TOK_DECLR_INIT;

	// 		add_child(arg, parents->first->value);
	// 		insert(0, arg, parents);
	// 	} fordeclrlist { /* TODO: Tem que poder fazer várias declarações sem iniciar */
	// 		removeAt(0, parents);
	// 	} fortail fortail
	// | TYPE ID
	// 	{
	// 		node_t arg = create_node(create_syn_val(SYN_TAG, TOK_DECLR));
	// 		add_child($1, arg);
	// 		add_child($2, arg);

	// 		ADD_CONTEXT(CTX_VAR, SYN_EXP(FIRSTCHILD_VALUE($2))->name, SYN_TYPE(FIRSTCHILD_VALUE($1))->name);

	// 		add_child(arg, parents->first->value);
	// 		insert(0, arg, parents);
	// 	} idlist {
	// 		removeAt(0, parents);
	// 	} fortail fortail
	/* | */exp
		{
			add_child($1, parents->first->value);
		} fortail fortail
	| fortail fortail
		{
			node_t exp = create_node(create_syn_val(SYN_TAG, TOK_EMPTYEXP));
			exp->parent = parents->first->value;
			prepend(exp, ((node_t)parents->first->value)->children);
		}
	/* Erros */
	| error
		{
			sprintf(syn_errormsg, "Invalid expression in for argument");
			HANDLE_ERROR(syn_errormsg);
		}
// fordeclrlist: %empty
//  	| ',' ID '=' exp fordeclrlist
//  		{
//  			add_child($2, parents->first->value);
//  			add_child($4, parents->first->value);
//  		}
//  	;
	/* NOTE: esse ponto e virgula vem antes*/ ;


fortail: ';' exp
		{
			add_child($2, parents->first->value);
		}
	| ';'
		{
			add_child(create_node(create_syn_val(SYN_TAG, TOK_EMPTYEXP)), parents->first->value);
		}
	;

idlist: %empty
	| ',' ID
		{
			node_t type_node = child_at(0, parents->first->value);
			ADD_CONTEXT(CTX_VAR, SYN_EXP(FIRSTCHILD_VALUE($2))->name, SYN_TYPE(FIRSTCHILD_VALUE(type_node))->name);
			add_child($2, parents->first->value);
		} idlist
	| ',' error
		{
			add_child(create_node(create_syn_val(SYN_TAG, ERR_TOKEN)), parents->first->value);
			HANDLE_ERROR("Expected an identifier");
		} idlist
	;

exp: INT     { add_child($1, ($$ = create_node(create_syn_val(SYN_TAG, TOK_INT))));    }
	| FLOAT  { add_child($1, ($$ = create_node(create_syn_val(SYN_TAG, TOK_FLOAT))));  }
	| STRING { add_child($1, ($$ = create_node(create_syn_val(SYN_TAG, TOK_STRING)))); }
	| CHAR   { add_child($1, ($$ = create_node(create_syn_val(SYN_TAG, TOK_CHAR))));   }
	| EMPTY  {
			SYN_exp_t exp = SYN_EXP(create_syn_val(SYN_EXP, strdup(TOK_EMPTY)));
			init_syn_exp(CTX_SET, 0, exp);
			$$ = create_node(exp);
		}
	| ID
		{
			$$ = $1;
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
		}
	| exp OPPOS
		{
			ADD_POS_EXP($$, $2, $1);
			if (strcmp(SYN_VALUE($1->value)->name, TOK_ID) != 0 ||
				lookup_symbol(
					SYN_VALUE(child_at(0, $1)->value)->name,
					current_context
					)->type != CTX_VAR) {
				yyerror(NULL, NULL, NULL);
				sprintf(
					syn_errormsg,
					"Operator \"%s\" must be used with a variable",
					SYN_VALUE($2->value)->name
					);
				HANDLE_ERROR(syn_errormsg);
			}
		}
	| OPPOS exp
		{
			ADD_UNI_EXP($$, $1, $2);
			if (strcmp(SYN_VALUE($2->value)->name, TOK_ID) != 0 ||
				lookup_symbol(
					SYN_VALUE(child_at(0, $2)->value)->name,
					current_context
					)->type != CTX_VAR) {
				yyerror(NULL, NULL, NULL);
				sprintf(
					syn_errormsg,
					"Operator \"%s\" must be used with a variable",
					SYN_VALUE($1->value)->name
					);
				HANDLE_ERROR(syn_errormsg);
			}
		}
	| '*' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '+' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '-' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '!' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '~' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
	| '&' exp %prec OPUNI { ADD_UNI_EXP($$, $1, $2);     }
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
			node_t exp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP));
			node_t op1 = create_node(create_syn_val(SYN_TAG, TOK_OPTER));
			node_t op2 = create_node(create_syn_val(SYN_TAG, TOK_OPTER));
			add_child($<node>2, op1);
			add_child($<node>4, op2);
			add_child($1, exp);
			add_child(op1, exp);
			add_child($3, exp);
			add_child(op2, exp);
			add_child($5, exp);
			$$ = exp;
			eval_exp_type(exp);
		}
	| ID OPASSIGN exp
		{
			node_t exp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP));
			node_t op = create_node(create_syn_val(SYN_TAG, TOK_OPASSIGN));
			if (operator_code(SYN_VALUE($2->value)->name) != OP_ASSIGN) {
				/* Separa o operador composto em dois diferentes: '+' e '='
				para '+=', por exemplo */
				const char *opassign = operator_string(OP_ASSIGN);
				char *midop = strdup(SYN_VALUE($2->value)->name);
				midop[strlen(midop) - strlen(opassign)] = '\0';
				midop = (char *) realloc(midop, strlen(midop) + 1);
				free(SYN_VALUE($2->value)->name);
				SYN_VALUE($2->value)->name = strdup(opassign);
				SYN_OP($2->value)->op_type = OP_ASSIGN;
				/* Cria uma expresão intermediária usando midop */
				node_t midexp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP));
				node_t midoptag = create_node(create_syn_val(SYN_TAG, TOK_OPBIN));
				add_child(create_node(create_syn_val(SYN_OP, midop)), midoptag);
				init_syn_op(
					operator_code(midop),
					child_at(0, midoptag)->value
					);
				/* Cria uma cópia do id */
				node_t id_copy = create_node(create_syn_val(SYN_TAG, TOK_ID));
				SYN_exp_t id_exp_copy = SYN_EXP(
					create_syn_val(
						SYN_EXP,
						strdup(
							SYN_EXP(((node_t)$1->children->first->value)->value)->name
							)
						)
					);
				init_syn_exp(CTX_UNK, 0, id_exp_copy);
				add_child(create_node(id_exp_copy), id_copy);
				add_child(id_copy, midexp);
				add_child(midoptag, midexp);
				add_child($3, midexp);

				add_child($2, op);
				add_child($1, exp);
				add_child(op, exp);
				add_child(midexp, exp);
			} else {
				add_child($2, op);
				add_child($1, exp);
				add_child(op, exp);
				add_child($3, exp);
			}
			$$ = exp;
			eval_exp_type(exp);
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
		}
	| ID
		{
			$<node>$ = create_node(create_syn_val(SYN_FUN, TOK_FN));
			add_child($1, $<node>$);
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
			insert(0, $<node>$, parents);
		} fntail {
			CTX_sym_t maybe_fun =
				lookup_symbol(SYN_VALUE(FIRSTCHILD_VALUE($1))->name, context);
			if (maybe_fun == NULL || maybe_fun->type != CTX_FUN) {
				yyerror(NULL, NULL, NULL);
				sprintf(
					syn_errormsg,
					"Invalid call to \"%s\" (not a function)",
					SYN_VALUE(FIRSTCHILD_VALUE($1))->name
					);
				HANDLE_ERROR(syn_errormsg);
			}
			$$ = $<node>2;
			removeAt(0, parents);
		}
	| '(' exp ')'
		{
			// add_child($2, ($$ = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP))));
			$$ = $2;
			eval_exp_type($$);
		}
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
			node_t exp = create_node(create_syn_val(SYN_EXP_COMP, TOK_EXP));
			node_t op = create_node(create_syn_val(SYN_TAG, TOK_OPASSIGN));
			add_child($2, op);
			add_child($1, exp);
			add_child(op, exp);
			node_t err = create_node(create_syn_val(SYN_TAG, ERR_TOKEN));
			add_child(err, exp);
			$$ = exp;
			UNDEF_ID_ERR(FIRSTCHILD_VALUE($1));
			ssprintf(
				syn_errormsg,
				"Expected expression in '%s %s'",
				SYN_EXP(FIRSTCHILD_VALUE($1))->name,
				SYN_OP($2->value)->name
				);
			HANDLE_ERROR(syn_errormsg);
		}
	;

fntail: '(' arglist ')'
		{
			node_t fn_syn = parents->first->value;
			char *fn_name = SYN_VALUE(FIRSTCHILD_VALUE(fn_syn->children->first->value))->name;
			CTX_sym_t fn_sym = lookup_symbol(fn_name, current_context);
			if (fn_sym != NULL &&
				fn_sym->type == CTX_FUN &&
				CTX_FUN(fn_sym)->params != NULL) {
				size_t fn_args_count = fn_syn->children->size - 1;
				/** TODO: checar in-exp
				* Se é uma função que suporta (padrões)
				* Separar em elem e set
				* Checar se é elem e set??
				*/
				list_t arg_list = create_list();
				// printf("=========\n%s\n", fn_name);
				// MAP({
				// 	printf(">> %s\n", data_type_string(eval_exp_type(MAP_val)));
				// }, fn_syn->children);
				if (CTX_FUN(fn_sym)->params->size != fn_args_count) {
					yyerror(NULL, NULL, NULL);
					ssprintf(
						syn_errormsg,
						"Expected %lu arguments in %s() call (found %lu)",
						CTX_FUN(fn_sym)->params->size,
						fn_name,
						fn_args_count
						);
					HANDLE_ERROR(syn_errormsg);
				} else {
					if (strcmp(fn_name, BUILTIN_READ) == 0) {
						node_t arg = child_at(fn_syn->children->size - 1, fn_syn);
						char *id_name = SYN_VALUE(child_at(0, arg)->value)->name;
						CTX_sym_t id_sym = lookup_symbol(id_name, current_context);
						if (strcmp(SYN_VALUE(arg->value)->name, TOK_ID) != 0 || id_sym->type != CTX_VAR) {
							yyerror(NULL, NULL, NULL);
							ssprintf(
								syn_errormsg,
								"Expression must be a variable in \""BUILTIN_READ"\" call"
								);
							HANDLE_ERROR(syn_errormsg);
						} else if (id_sym != NULL &&
									(id_sym->data_type == CTX_SET ||
									(id_sym->data_type == CTX_ELEM &&
									CTX_VAR(id_sym)->secondary_data_type == CTX_UNK))) {
							yyerror(NULL, NULL, NULL);
							ssprintf(
								syn_errormsg,
								"Can not read into a %s or untyped %s in \""BUILTIN_READ"\" call",
								data_type_string(CTX_SET),
								data_type_string(CTX_ELEM)
								);
							HANDLE_ERROR(syn_errormsg);
						}
					}
					iter_t it_pars = ITERATOR(CTX_FUN(fn_sym)->params, ITER_DOWN);
					iter_t it_args = ITERATOR(fn_syn->children, ITER_DOWN);
					while (ITER_HAS(it_pars)) {
						CTX_sym_t par = ITER(it_pars, CTX_sym_t, NULL);
						int par_type = par->data_type;
						int arg_type = eval_exp_type(ITER(it_args, node_t, NULL));

						/** Checa se a in-expression de exists() tem uma variável
						  * na esquerda
						  */
						if (strcmp(fn_name, BUILTIN_EXISTS) == 0 &&
							arg_type == CTX_INEXP &&
							strcmp(
								SYN_VALUE(FIRSTCHILD_VALUE(ITER_OLD(it_args)))->name,
								TOK_ID
								) != 0
						) {
							yyerror(NULL, NULL, NULL);
							ssprintf(
								syn_errormsg,
								"Left-hand side of expression must be an identifier"
								);
							HANDLE_ERROR(syn_errormsg);
						}
						if (!can_cast(arg_type, par_type)) {
							yyerror(NULL, NULL, NULL);
							ssprintf(
								syn_errormsg,
								"Can not cast %s value to %s for the parameter \"%s\" of %s()",
								data_type_string(arg_type),
								data_type_string(par_type),
								par->id,
								fn_name
								);
							HANDLE_ERROR(syn_errormsg);
						}
					}
				}
				delete_list(arg_list);
			}
		}
	| '(' arglist error { HANDLE_ERROR("Expected ')'"); }
	;

arglist: %empty
	| exp { add_child($1, parents->first->value); } argtail
	;

argtail: %empty
	| ',' exp { add_child($2, parents->first->value); } argtail
	;

%%

int yyerror(int *max, int *children_count, char *s) {
	SET_ERROR_LOCATION(lnum, lcol, err_loc);
	return 0;
}

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsnprintf(target, NAMESIZE, template, ap);
	va_end(ap);
}

int validate_breaks(node_t node, void *data) {
	int ret_code = 0;
	if (node->parent != NULL) {
		char *token = SYN_VALUE(node->value)->name;
		if (strcmp(token, TOK_BREAK) == 0) {
			int in_loop = 0;
			while (node->parent != NULL) {
				token = SYN_VALUE(node->value)->name;
				if (strcmp(token, TOK_WHILE) == 0 ||
					strcmp(token, TOK_FOR) == 0 ||
					strcmp(token, TOK_FORALL) == 0) {
					in_loop = 1;
					break;
				}
				node = node->parent;
			}
			if (!in_loop) {
				yyerror(NULL, NULL, NULL);
				HANDLE_ERROR("Can not use break outside of loop statement");
			}
			ret_code = 1;
		}
	}
	return ret_code;
}

int print(node_t node, void *data) {
	print_data_t *data_st = data;

	int *children_count = data_st->children_count;

	size_t l = level(node);

	int is_last = 1;

	if (!data_st->only_spaces) {
		node_t lookback = node->parent;
		node_t last_valid = node->parent, last_valid_child = node;

		char *node_name = SYN_VALUE(node->value)->name;
		if (!data_st->detailed &&
			node->children->size == 1 &&
			strcmp(node_name, TOK_RETURN) != 0) {
			return 0;
		}
		if(!data_st->detailed) {
			size_t folds = 0;
			int searching = 1;
			while (lookback != NULL) {
				char *node_name = SYN_VALUE(lookback->value)->name;
				if (lookback->children->size > 1 ||
					strcmp(node_name, TOK_RETURN) == 0) {
					searching = 0;
				} else if (++folds && searching) {
					last_valid_child = last_valid;
					last_valid = last_valid->parent;
				}
				lookback = lookback->parent;
			}
			l -= folds;
		}

		children_count[l - 1] = node->children->size;

		/* Checa se este nó é o último filho */
		if (last_valid != NULL) {
			int idx = indexOf(last_valid_child, last_valid->children);
			is_last = idx < 0 || idx == last_valid->children->size - 1;
		}
		if (is_last) {
			/* Desabilita a impressão de TREECHILD */
			children_count[l - 1] = 0;
		}

		/* Imprime os espaços e TREECHILD necessários */
		for (size_t i = 0; i < l - 1; i++) {
			printf("%s ", children_count[i] ? TREECHILD : " ");
		}
		/* Se não é o nó raiz */
		if (l > 1) { printf( /* NOTE: 6 caracteres no total */
				"%s" TREEBRANCH "%s" TREEBRANCH TREELEAF " ",
				is_last ? TREECHILDLAST : TREECHILDMID,
				node->children->size ? TREECHILDFIRST : TREEBRANCH
				);
		}

		data_st->val_print(node);
		printf("\n");
	} else {
		for (size_t i = 0; i < l; i++) {
			printf("%s ", children_count[i] ? TREECHILD : " ");
		}
		/* NOTE: 4 caracteres */
		printf(
			"%s " TREEEXTENSION " ",
			node->children->size ? TREECHILD : " "
			);
	}
	return 0;
}

void print_syntatic(node_t node) {
	printf("%s",
		node->children->size > 0 && node->parent != NULL ?
			TREEFADECOLOR :
			TREEACCENTCOLOR
		);

	int is_char = 0;
	if (SYN_VALUE(node->value)->type == SYN_EXP &&
		SYN_EXP(node->value)->data_type == CTX_CHAR) {
		is_char = 1;
		if (SYN_EXP(node->value)->depth == 1) {
			is_char = 2;
		}
	}

	char *escaped = NULL;
	if (node->parent != NULL) {
		escaped = unscape(SYN_VALUE(node->value)->name);
	}
	printf(
		"%s%s%s%s" PARSER_CLEARCOLOR,
		node->parent == NULL ? "\033[4m" : "",
		is_char == 1 ? "'" : (is_char == 2 ? "\"" : ""),
		node->parent == NULL ? (char *) node->value : escaped,
		is_char == 1 ? "'" : (is_char == 2 ? "\"" : "")
		);
	if (escaped != NULL) {
		free(escaped);
	}

	if ((SYN_VALUE(node->value)->type == SYN_EXP ||
		SYN_VALUE(node->value)->type == SYN_EXP_COMP) &&
		SYN_EXP(node->value)->cast != CTX_INV) {
		printf(
			TREEFADECOLOR" (as %s)"PARSER_CLEARCOLOR,
			data_type_string(SYN_EXP(node->value)->cast)
			);
	}
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
				"%s%s: (%s%s%s) \"" TREEACCENTCOLOR "%s" PARSER_CLEARCOLOR "\"",
				node->parent == NULL && it == ((list_t)node->value)->first?
					TREEBRANCH TREEBRANCH TREECHILDFIRST TREEBRANCH  TREELEAF " " :
					"",
				type_string(sym->type),
				data_type_string(sym->data_type),
				sym->type == CTX_VAR &&
				CTX_VAR(sym)->secondary_data_type != CTX_UNK ?
				": " : "",
				sym->type == CTX_VAR &&
				CTX_VAR(sym)->secondary_data_type != CTX_UNK ?
				data_type_string(CTX_VAR(sym)->secondary_data_type) :
				"",
				sym->id
				);
			if (sym->type == CTX_FUN) {
				printf(" (");
				if (CTX_FUN(sym)->params != NULL) {
					MAP(
						printf(
							"%s%s",
							data_type_string(CTX_SYM(MAP_val)->data_type),
							MAP_i < CTX_FUN(sym)->params->size - 1 ? ", " : ""
							)
					, CTX_FUN(sym)->params);
				}
				printf(")");
			}
			if (sym->lnum >= 0 && sym->lcol > 0) {
				printf(TREEFADECOLOR" @%d:%d"PARSER_CLEARCOLOR, sym->lnum, sym->lcol);
			}
			if (it->next != NULL) {
				printf("\n");
				print(node, &data);
			}
		}
	}
	free(children_count);
}

int max_level(node_t node, void *data) {
	int *max = (int *) data;
	int l = level(node);
	if (*max < l) *max = l;
	return 0;
}

int create_context_table(node_t node, void *data) {
	set_t ctx_set = data;
	MAP({
		set_elem_t el = create_set_elem(0, MAP_val, compare_symbol, NULL);
		if (!set_add(el, ctx_set)) {
			delete_set_elem(el);
		}
	}, node->value);
	return 0;
}

int free_values(node_t node, void *data) {
	/* node_t -> SYN_value_t  */
	if (strcmp(node->value, filename)) {
		delete_syn_val(node->value);
	}
	return 0;
}

int free_context(node_t node, void *data) {
	MAP({
		delete_symbol(MAP_val);
	}, node->value);
	delete_list(node->value);
	return 0;
}

void init_context(node_t node) {
	/*
	int write(T object)
	int writeln(T object)
	int read(T output)
	int is_set(elem el)
	set add(inexp exp)
	set remove(inexp exp)
	elem exists(inexp exp)
	*/
	CTX_sym_t sym = NULL;

	CTX_sym_t write   = create_symbol(CTX_FUN, BUILTIN_WRITE, CTX_INT, -1, -1);
	append(write  , node->value);
	PUSH_CONTEXT;
	ADD_CONTEXT(CTX_VAR, "object", "elem");
	sym = lookup_symbol("object", current_context);
	append(sym, (CTX_FUN(write)->params = create_list()));
	POP_CONTEXT;

	CTX_sym_t writeln = create_symbol(CTX_FUN, BUILTIN_WRITELN, CTX_INT, -1, -1);
	append(writeln, node->value);
	PUSH_CONTEXT;
	ADD_CONTEXT(CTX_VAR, "object", "elem");
	sym = lookup_symbol("object", current_context);
	append(sym, (CTX_FUN(writeln)->params = create_list()));
	POP_CONTEXT;

	CTX_sym_t read    = create_symbol(CTX_FUN, BUILTIN_READ, CTX_INT, -1, -1);
	append(read   , node->value);
	PUSH_CONTEXT;
	ADD_CONTEXT(CTX_VAR, "output", "elem");
	sym = lookup_symbol("output", current_context);
	append(sym, (CTX_FUN(read)->params = create_list()));
	POP_CONTEXT;

	CTX_sym_t is_set  = create_symbol(CTX_FUN, BUILTIN_ISSET, CTX_INT, -1, -1);
	append(is_set , node->value);
	PUSH_CONTEXT;
	ADD_CONTEXT(CTX_VAR, "element", "elem");
	sym = lookup_symbol("element", current_context);
	append(sym, (CTX_FUN(is_set)->params = create_list()));
	POP_CONTEXT;

	CTX_sym_t add     = create_symbol(CTX_FUN, BUILTIN_ADD, CTX_SET, -1, -1);
	append(add    , node->value);
	PUSH_CONTEXT;
	ADD_CONTEXT(CTX_VAR, "expression", "in-expression");
	sym = lookup_symbol("expression", current_context);
	append(sym, (CTX_FUN(add)->params = create_list()));
	POP_CONTEXT;

	CTX_sym_t remove  = create_symbol(CTX_FUN, BUILTIN_REMOVE, CTX_SET, -1, -1);
	append(remove , node->value);
	PUSH_CONTEXT;
	ADD_CONTEXT(CTX_VAR, "expression", "in-expression");
	sym = lookup_symbol("expression", current_context);
	append(sym, (CTX_FUN(remove)->params = create_list()));
	POP_CONTEXT;

	CTX_sym_t exists  = create_symbol(CTX_FUN, BUILTIN_EXISTS, CTX_ELEM, -1, -1);
	append(exists , node->value);
	PUSH_CONTEXT;
	ADD_CONTEXT(CTX_VAR, "expression", "in-expression");
	sym = lookup_symbol("expression", current_context);
	append(sym, (CTX_FUN(exists)->params = create_list()));
	POP_CONTEXT;

}

void print_context_table() {
	/* Cria e popula um conjunto de símbolos */
	set_t ctx_set = create_set();
	depth_pre(
		create_context_table,
		context,
		ctx_set,
		NULL,
		NULL
		);
	/* Só valores pares */
	int type_len = 10, data_type_len = 6, id_len = 16;

	/* Borda superior */
	printf(BOX_TOP_LEFT);
	for (int i = 0; i < type_len; i++) printf(BOX_HOR);
	printf(BOX_CROSS_TOP);
	for (int i = 0; i < data_type_len; i++) printf(BOX_HOR);
	printf(BOX_CROSS_TOP);
	for (int i = 0; i < id_len; i++) printf(BOX_HOR);
	printf(BOX_TOP_RIGHT"\n");

	/* Cabeçalho */
	printf(
		BOX_VERT"%*s%-*.*s"BOX_VERT"%*s%-*.*s"BOX_VERT"%*s%-*.*s"BOX_VERT"\n",
			/* Espaços */
		(int) (type_len - strlen("simbolo ")) / 2, "",
			/* Título + Espaços */
		(int) (type_len + strlen("simbolo ")) / 2,
		type_len, "simbolo",
			/* Espaços */
		(int) (data_type_len - strlen("tipo")) / 2, "",
			/* Título + Espaços */
		(int) (data_type_len + strlen("tipo")) / 2,
		data_type_len, "tipo",
			/* Espaços */
		(int) (id_len - strlen("identificador ")) / 2, "",
			/* Título + Espaços */
		(int) (id_len + strlen("identificador ")) / 2,
		id_len, "identificador"
		);
	/* Separador do cabeçalho */
	printf(BOX_HEADER_LEFT);
	for (int i = 0; i < type_len; i++) printf(BOX_HEADER_HOR);
	printf(BOX_HEADER_MID);
	for (int i = 0; i < data_type_len; i++) printf(BOX_HEADER_HOR);
	printf(BOX_HEADER_MID);
	for (int i = 0; i < id_len; i++) printf(BOX_HEADER_HOR);
	printf(BOX_HEADER_RIGHT"\n");
	/* Valores da tabela */
	MAP({
		/* Obtém o símbolo atual */
		CTX_sym_t sym =
			CTX_SYM(SET_ELEM(MAP_val)->value);
		printf(BOX_VERT);
		/* Imprime o tipo do símbolo */
		printf(
			"%-*.*s"BOX_VERT,
			type_len,
			type_len,
			type_string(sym->type)
			);
		/* Imprime o tipo de dados do símbolo */
		printf(
			"%-*.*s"BOX_VERT,
			data_type_len,
			data_type_len,
			data_type_string(sym->data_type)
			);
		/* Imprime o identificador do símbolo */
		printf(
			"%-*.*s"BOX_VERT"\n",
			id_len,
			id_len,
			sym->id
			);
	}, ctx_set);
	/* Borda inferior */
	printf(BOX_BOT_LEFT);
	for (int i = 0; i < type_len; i++) printf(BOX_HOR);
	printf(BOX_CROSS_BOT);
	for (int i = 0; i < data_type_len; i++) printf(BOX_HOR);
	printf(BOX_CROSS_BOT);
	for (int i = 0; i < id_len; i++) printf(BOX_HOR);
	printf(BOX_BOT_RIGHT"\n");
	/* Limpa o conjunto de símbolos */
	delete_set(ctx_set);
}

int main(int argc, char **argv) {
	int show_context = 1, show_syntatic_tree = 1, show_table = 0, show_detailed = 0;
	char c, *farg = NULL;
	while ((c = getopt(argc, argv, "CStdh")) != -1) {
		switch (c) {
		case 'C':
			show_context = 0;
			break;
		case 'S':
			show_syntatic_tree = 0;
			break;
		case 't':
			show_table = 1;
			break;
		case 'd':
			show_detailed = 1;
			break;
		case 'h':
			printf("%s [OPTIONS] FILE [OPTIONS]\n", argv[0]);
			printf("\t-C\tinibe a impressão da árvore de contexto\n");
			printf("\t-S\tinibe a impressão da árvore sintática de contexto\n");
			printf(
				"\t-t\timprime uma tabela com cada símbolo encontrado de "
				"nome diferente\n");
			printf("\t-d\timprime a árvore sintática com detalhes\n");
			printf("\t-h\timprime esta mensagem de ajuda e sai\n");
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
		yyerror(NULL, NULL, NULL);
		sprintf(syn_errormsg, "Unexpected end of file");
		HANDLE_ERROR(syn_errormsg);
	}

		/* Traduz para TAC */
	if (!got_error) {
		translate(root, context);
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
			0,                                              /**/
			1                                               /**/
			};                                              /**/
		depth_pre(print, context, &ctx_data, NULL, NULL);   /**/
		free(children_count);                               /**/
	}                                                       /**/
                                                            /**/
	/* =============== INÍCIO DA TABELA =================*/ /**/
	if (show_table) {                                       /**/
		print_context_table();                              /**/
	}                                                       /**/
	/* ================= FIM DA TABELA ==================*/ /**/
                                                            /**/
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
			0,                                              /**/
			show_detailed                                   /**/
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
