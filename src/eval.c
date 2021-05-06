#include <context.h>
#include <eval.h>
#include <set.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>
#include <util.h>

/**
 * Para ter acesso às funcionalidade de reportar erro do util.h
 */
extern int lnum, lcol;
extern char filename[FILENAMESIZE + 1];
extern char syn_errormsg[NAMESIZE + 1];
extern list_t err_loc;
extern int got_error;

int eval_exp_type(node_t exp) {
  if (exp == NULL) {
    fprintf(stderr, "Invalid pointer in eval_exp_type()\n");
  }
  int exp_type = CTX_UNK;
  /* Trata uma expressão simples (identificador, constante ou chamada de função)
   */
  if (SYN_VALUE(exp->value)->type == SYN_EXP) {
    exp_type = SYN_EXP(exp->value)->data_type;
    if (SYN_EXP(exp->value)->data_type == CTX_ELEM) {
      extern node_t current_context;
      CTX_sym_t sym = lookup_symbol(SYN_EXP(exp->value)->name, current_context);
      if (sym != NULL && sym->type == CTX_VAR && sym->data_type == CTX_ELEM &&
          CTX_VAR(sym)->secondary_data_type != CTX_UNK) {
        exp_type = CTX_VAR(sym)->secondary_data_type;
      }
    }
    /* Pode não ter um tipo detectado se não for uma constante */
    if (exp_type == CTX_UNK) {
      extern node_t current_context;
      CTX_sym_t sym = lookup_symbol(SYN_EXP(exp->value)->name, current_context);
      /* Atualizar com o tipo detectado */
      if (sym != NULL) {
        exp_type = sym->data_type;
        switch (sym->type) {
        case CTX_VAR:
          init_syn_exp(exp_type, CTX_VAR(sym)->depth, exp->value);
          break;
        case CTX_FUN:
          SYN_EXP(exp->value)->data_type = exp_type;
          break;
        default:
          fprintf(stderr, "Invalid symbol type in eval_exp_type()\n");
          exit(EXIT_FAILURE);
        }
      } /* O else é quando tem o erro do identificador não estar definido */
    }
    // print_syn_exp(exp->value);
    // printf(" %s", SYN_EXP(exp->value)->name);
    // printf("\n");
  } else if (SYN_VALUE(exp->value)->type == SYN_EXP_COMP) {
    if (SYN_EXP_COMP(exp->value)->data_type == CTX_UNK) {
      SYN_op_t op1 = NULL, op2 = NULL;
      SYN_exp_t val1 = NULL; // , val2 = NULL, val3 = NULL;
      node_t subexp1 = NULL, subexp2 = NULL, subexp3 = NULL;
      switch (exp->children->size) {
      case 1: /* Expressão constante, identificador ou tag */
        exp_type = eval_exp_type(exp->children->first->value);
        break;
      case 2: /* Operação unária */
        if (SYN_VALUE(((node_t)((node_t)exp->children->first->value)
                           ->children->first->value)
                          ->value)
                ->type == SYN_OP) {
          op1 = ((node_t)((node_t)exp->children->first->value)
                     ->children->first->value)
                    ->value;
          subexp1 = exp->children->last->value;
          val1 = ((node_t)subexp1->children->first->value)->value;
        } else {
          op1 = ((node_t)((node_t)exp->children->last->value)
                     ->children->first->value)
                    ->value;
          subexp1 = exp->children->first->value;
          val1 = ((node_t)subexp1->children->first->value)->value;
        }
        exp_type = eval_exp_type(subexp1);
        switch (op1->op_type) {
        case OP_PLUS:
        case OP_MINUS:
        case OP_UNI_INC:
        case OP_UNI_DEC:
        case OP_POS_INC:
        case OP_POS_DEC:
          if (val1->depth == 0 && !can_cast(exp_type, CTX_FLOAT)) {
            SET_ERROR_LOCATION(lnum, lcol, err_loc);
            sprintf(syn_errormsg, "Operator \"%s\" not supported for type %s",
                    op1->name, data_type_string(exp_type));
            HANDLE_ERROR(syn_errormsg);
          }
          break;
        case OP_STAR:
          if (val1->depth == 0) {
            SET_ERROR_LOCATION(lnum, lcol, err_loc);
            sprintf(syn_errormsg,
                    "Dereference not supported on non-pointer type %s",
                    data_type_string(exp_type));
            HANDLE_ERROR(syn_errormsg);
          }
          break;
        case OP_UNI_REF:
          break;
        case OP_UNI_NEG:
        case OP_UNI_BIT_NEG:
          /* TODO: nada? */
          break;
        default:
          fprintf(stderr, "Invalid unary operator in eval_exp_type()\n");
          exit(EXIT_FAILURE);
        }
        break;
      case 3: /* Operação binária */
        subexp1 = exp->children->first->value;
        op1 = ((node_t)((node_t)exp->children->first->next->value)
                   ->children->first->value)
                  ->value;
        subexp2 = exp->children->last->value;
        if (subexp2->children->size == 1) {
          /* O elem pega o tipo da outra variável se não tiver */
          subexp3 = subexp2->children->first->value;
          if (SYN_VALUE(subexp3->value)->type == SYN_EXP) {
            extern node_t current_context;
            CTX_sym_t sym =
                lookup_symbol(SYN_EXP(subexp3->value)->name, current_context);
            if (sym != NULL && sym->type == CTX_VAR &&
                CTX_VAR(sym)->data_type == CTX_ELEM &&
                CTX_VAR(sym)->secondary_data_type == CTX_UNK) {
              CTX_VAR(sym)->secondary_data_type = eval_exp_type(subexp1);
              SYN_EXP(subexp3->value)->data_type = eval_exp_type(subexp1);
            }
          }
        }
        if (subexp1->children->size == 1) {
          subexp3 = subexp1->children->first->value;
          if (SYN_VALUE(subexp3->value)->type == SYN_EXP) {
            extern node_t current_context;
            CTX_sym_t sym =
                lookup_symbol(SYN_EXP(subexp3->value)->name, current_context);
            if (sym != NULL && sym->type == CTX_VAR &&
                CTX_VAR(sym)->data_type == CTX_ELEM &&
                CTX_VAR(sym)->secondary_data_type == CTX_UNK) {
              CTX_VAR(sym)->secondary_data_type = eval_exp_type(subexp2);
              /* Perde a informação de que o tipo é polimórfico */
              SYN_EXP(subexp3->value)->data_type = eval_exp_type(subexp2);
              exp_type = eval_exp_type(subexp2);
            }
          }
        }
        switch (op1->op_type) {
        case OP_ASSIGN:
        case OP_ASSIGN_ADD:
        case OP_ASSIGN_SUB:
        case OP_ASSIGN_MUL:
        case OP_ASSIGN_DIV:
        case OP_ASSIGN_OR:
        case OP_ASSIGN_AND:
        case OP_ASSIGN_XOR:
          exp_type = eval_exp_type(subexp1);
          if (!can_cast(eval_exp_type(subexp2), exp_type)) {
            SET_ERROR_LOCATION(lnum, lcol, err_loc);
            sprintf(syn_errormsg, "Unable to cast expression of type %s to %s",
                    data_type_string(eval_exp_type(subexp2)),
                    data_type_string(exp_type));
            HANDLE_ERROR(syn_errormsg);
          } else {
            cast_to(exp_type, subexp2);
          }
          break;
        case OP_PLUS:
        case OP_MINUS:
        case OP_STAR:
        case OP_DIV:
        case OP_MOD:
          /* TODO: mensagem repetida no teste 3 para a = b + c */
          exp_type =
              eval_max_type(eval_exp_type(subexp1), eval_exp_type(subexp2));
          if (eval_max_type(exp_type, CTX_FLOAT) != CTX_FLOAT) {
            SET_ERROR_LOCATION(lnum, lcol, err_loc);
            sprintf(syn_errormsg,
                    "Operator \"%s\" not suppported between %s and %s",
                    operator_string(op1->op_type),
                    data_type_string(eval_exp_type(subexp1)),
                    data_type_string(eval_exp_type(subexp2)));
            HANDLE_ERROR(syn_errormsg);
          } else {
            cast_to(exp_type, subexp1);
            cast_to(exp_type, subexp2);
          }
          break;
        case OP_BIN_BIT_OR:
        case OP_BIN_BIT_AND:
        case OP_BIN_XOR:
        case OP_BIN_SHIFT_L:
        case OP_BIN_SHIFT_R:
          exp_type = eval_exp_type(subexp1);
          // if (eval_max_type(eval_exp_type(subexp2), CTX_INT) != CTX_INT) {
          // TODO: warning: não é int
          // }
          if (!can_cast(eval_exp_type(subexp2), CTX_INT)) {
            SET_ERROR_LOCATION(lnum, lcol, err_loc);
            sprintf(syn_errormsg, "Shift amount must be %s, not %s",
                    data_type_string(CTX_INT), data_type_string(exp_type));
            HANDLE_ERROR(syn_errormsg);
          }
          cast_to(CTX_INT, subexp2);
          break;
        case OP_BIN_OR:
        case OP_BIN_AND:
          /* Todos os tipos podem ser considerados bool */
          exp_type = CTX_INT;
          break;
        case OP_BIN_EQ:
        case OP_BIN_NEQ:
        case OP_BIN_LT:
        case OP_BIN_GT:
        case OP_BIN_LTE:
        case OP_BIN_GTE:
          /* Um valor bool */
          exp_type = CTX_INT;
          if (eval_max_type(eval_exp_type(subexp1), eval_exp_type(subexp2)) ==
              CTX_UNK) {
            SET_ERROR_LOCATION(lnum, lcol, err_loc);
            sprintf(syn_errormsg,
                    "Operator \"%s\" not supported between %s and %s",
                    operator_string(op1->op_type),
                    data_type_string(eval_exp_type(subexp1)),
                    data_type_string(eval_exp_type(subexp2)));
            HANDLE_ERROR(syn_errormsg);
          } else {
            cast_to(
                eval_max_type(eval_exp_type(subexp1), eval_exp_type(subexp2)),
                subexp1);
            cast_to(
                eval_max_type(eval_exp_type(subexp1), eval_exp_type(subexp2)),
                subexp2);
          }
          break;
        case OP_BIN_IN:
          exp_type = CTX_INEXP;
          /* Aparentemente o lado esquerdo pode ser de qualquer tipo */
          // if (eval_exp_type(subexp1) != CTX_ELEM) {
          //   SET_ERROR_LOCATION(lnum, lcol, err_loc);
          //   sprintf(syn_errormsg,
          //           "Left-hand side expression of operator \"%s\" must be of
          //           " "type %s (found %s)", operator_string(op1->op_type),
          //           data_type_string(CTX_ELEM),
          //           data_type_string(eval_exp_type(subexp1)));
          //   HANDLE_ERROR(syn_errormsg);
          // }
          eval_exp_type(subexp1); /* Para atualizar os tipos */
          if (eval_exp_type(subexp2) != CTX_SET) {
            SET_ERROR_LOCATION(lnum, lcol, err_loc);
            sprintf(syn_errormsg,
                    "Right-hand side expression of operator \"%s\" must be of "
                    "type %s (found %s)",
                    operator_string(op1->op_type), data_type_string(CTX_SET),
                    data_type_string(eval_exp_type(subexp2)));
            HANDLE_ERROR(syn_errormsg);
          }
          break;
        default:
          fprintf(stderr, "Invalid binary operator in eval_exp_type()\n");
          exit(EXIT_FAILURE);
        }
        break;
      case 5: /* Operação ternária */
        subexp1 = exp->children->first->value;
        // op1 = ((node_t)exp->children->first->next->value)->value;
        op1 = ((node_t)((node_t)exp->children->first->next->value)
                   ->children->first->value)
                  ->value;
        subexp2 = exp->children->first->next->next->value;
        // op2 = ((node_t)exp->children->last->prev->value)->value;
        op2 = ((node_t)((node_t)exp->children->last->prev->value)
                   ->children->first->value)
                  ->value;
        subexp3 = exp->children->last->value;
        exp_type =
            eval_max_type(eval_exp_type(subexp2), eval_exp_type(subexp3));
        /* Se for CTX_UNK então os dois tipos não são compatíveis */
        if (exp_type == CTX_UNK) {
          SET_ERROR_LOCATION(lnum, lcol, err_loc);
          sprintf(syn_errormsg,
                  "Type %s is incompatible with %s in \"%s %s\" operator",
                  data_type_string(eval_exp_type(subexp2)),
                  data_type_string(eval_exp_type(subexp3)),
                  operator_string(op1->op_type), operator_string(op2->op_type));
          HANDLE_ERROR(syn_errormsg);
        } else {
          cast_to(exp_type, subexp2);
          cast_to(exp_type, subexp3);
        }
        break;
      default:
        fprintf(stderr, "Badly formed expression in eval_exp_type()\n");
        exit(EXIT_FAILURE);
      }

      SYN_EXP_COMP(exp->value)->data_type = exp_type;
    } else {
      exp_type = SYN_EXP_COMP(exp->value)->data_type;
    }
  } else { /* Uma tag qualquer */
    exp_type = eval_exp_type(exp->children->first->value);
  }

  return exp_type;
}

int eval_max_type(int type1, int type2) {
  /*
   *        unknown
   *        /    |
   *     elem    |
   *      /  \   |
   * float  set inexp
   *   |
   *  int
   *   |
   *  char
   */
  int max_type = CTX_UNK;
  switch (type1) {
  case CTX_CHAR:
    if (type2 == CTX_ELEM) {
      max_type = type1;
    } else if (type2 == CTX_CHAR || type2 == CTX_INT || type2 == CTX_FLOAT) {
      max_type = type2;
    } else {
      max_type = CTX_UNK;
    }
    break;
  case CTX_INT:
    if (type2 == CTX_CHAR || type2 == CTX_ELEM) {
      max_type = type1;
    } else if (type2 == CTX_INT || type2 == CTX_FLOAT) {
      max_type = type2;
    } else {
      max_type = CTX_UNK;
    }
    break;
  case CTX_FLOAT:
    if (type2 == CTX_CHAR || type2 == CTX_INT || type2 == CTX_ELEM) {
      max_type = type1;
    } else if (type2 == CTX_FLOAT) {
      max_type = type2;
    } else {
      max_type = CTX_UNK;
    }
    break;
  case CTX_ELEM:
    if (type2 == CTX_ELEM) {
      max_type = CTX_UNK;
    } else {
      max_type = type2;
    }
    break;
  case CTX_SET:
    if (type2 == CTX_SET || type2 == CTX_ELEM) {
      max_type = type1;
    } else {
      max_type = CTX_UNK;
    }
    break;
  case CTX_INEXP:
    if (type2 == CTX_INEXP) {
      max_type = type2;
    } else {
      max_type = CTX_UNK;
    }
  case CTX_UNK:
    max_type = CTX_UNK;
    break;
  default:
    fprintf(stderr, "Unknown data type in eval_max_type()\n");
  }
  return max_type;
}

int can_cast(int type1, int type2) {
  int can = 1;
  switch (type1) {
  case CTX_CHAR:
  case CTX_INT:
  case CTX_FLOAT:
    if (type2 == CTX_SET) {
      can = 0;
    }
    break;
  case CTX_ELEM:
    can = 1; // type1 == type2;
    break;
  case CTX_SET:
    if (type2 == CTX_CHAR || type2 == CTX_INT || type2 == CTX_FLOAT) {
      can = 0;
    }
    break;
  case CTX_INEXP:
  case CTX_UNK:
    break;
  default:
    fprintf(stderr, "Invalid type in can_cast()\n");
    exit(EXIT_FAILURE);
  }
  return can;
}
