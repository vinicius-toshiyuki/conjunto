#include <context.h>
#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syntatic_node.h>
#include <translation.h>
#include <unistd.h>
#include <util.h>

t9n_t create_t9n(int type, void *value) {
  t9n_t t9n = (t9n_t)malloc(sizeof(struct t9n));
  t9n->type = type;
  t9n->value = value;
  return t9n;
}
void delete_t9n(t9n_t t9n) { free(t9n); }

void translate(node_t tree, node_t context) {
  /* Preencher .table com context */
  /* Definir funções de tree */
  create_table(context); /* TODO: tirar variável, pôr strings */
  create_code(tree, context);
}

void create_table(node_t context) {
  depth_pre(__create_table, context, NULL, __create_table_header, NULL);
}

void __create_table_header() { printf(".table\n"); }

int __create_table(node_t node, void *data) {
  MAP(
      {
        CTX_sym_t sym = MAP_val;
        switch (sym->data_type) {
        case CTX_CHAR:
        case CTX_INT:
        case CTX_FLOAT:
          if (sym->type == CTX_VAR) {
            printf("%s ", data_type_string(sym->data_type));
            printf("%s\n", sym->id);
          }
          break;
        case CTX_ELEM:
          /* TODO: cuidar em no .code */
          break;
        case CTX_SET:
          /* TODO: cuidar no .code com mema */
          break;
        case CTX_INEXP:
          break;
        default:
          fprintf(stderr, "Unexpected type in __create_table(): %s\n",
                  data_type_string(sym->data_type));
          exit(EXIT_FAILURE);
        }
      },
      ((list_t)node->value));
  return 0;
}

void create_code(node_t tree, node_t context) {
  t9n_data_t data = {context, create_list(), NULL};
  append(calloc(1, sizeof(size_t)), data.temps);
  depth_pre(__create_code, tree, &data, __create_code_header, NULL);
  printf("nop\n");
  for_each(free_list, data.temps);
  delete_list(data.temps);
}
void __create_code_header() { printf(".code\n"); }

int __create_code(node_t node, void *value) {
  static size_t ifcount = 0, whilecount = 0;
  t9n_data_t data = *((t9n_data_t *)value);
  int ret_code = 0;
  SYN_value_t syn = node->value;
  // if (node->parent != NULL)
  //   printf("%s %lu\n", syn->name, node->children->size);
  size_t *temp = data.temps->last->value;
  switch (syn->type) {
  case SYN_TAG:
    if (strcmp(syn->name, TOK_DECLR_FN) == 0) {
      // add_child(
      //     create_node(create_t9n(
      //         T9N_DECLR_FN, strdup(SYN_VALUE(node->children->first)->name))),
      //     t9n_tree);
      data.curfun = SYN_VALUE(child_at(0, child_at(1, node))->value)->name;
      /* TODO:feio */
      ((t9n_data_t *)value)->curfun = data.curfun;
      CTX_fun_t fun = CTX_FUN(lookup_symbol(data.curfun, data.context));
      data.context = fun->context;
      append(calloc(1, sizeof(size_t)), data.temps);
      printf("%s:\n", data.curfun);
    } else if (strcmp(syn->name, TOK_DECLR) == 0) {
      MAP(
          if (MAP_i > 0) {
            char *varname = SYN_VALUE(child_at(0, MAP_val)->value)->name;
            size_t idx = __get_declr_index(varname, data.curfun, data.context);
            if (idx > 0) {
              char *type =
                  SYN_VALUE(child_at(0, child_at(0, node))->value)->name;
              printf("// %s %s\n", type, varname);
              printf("mema $%lu, 1\n", (*temp)++);
            }
          },
          node->children);
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_RETURN) == 0) {
      printf("// return exp\n");
      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("return $%lu\n", *temp);
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_IF) == 0) {
      size_t tempif = ifcount++;
      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz IF_%lu, $%lu\n", tempif, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("IF_%lu:\n", tempif);
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_IF_ELSE) == 0) {
      size_t tempif = ifcount++;
      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz IF_%lu, $%lu\n", tempif, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("IF_%lu:\n", tempif);
      printf("pop $%lu\n", *temp);
      printf("brnz ELSE_%lu, $%lu\n", tempif, *temp);
      depth_pre(__create_code, child_at(2, node), value, NULL, NULL);
      printf("ELSE_%lu:\n", tempif);
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_WHILE) == 0) {
      size_t tempwh = whilecount++;
      printf("WHILE_%lu:\n", tempwh);
      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz WHILE_END_%lu, $%lu\n", tempwh, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("jump WHILE_%lu\n", tempwh);
      printf("WHILE_END_%lu:\n", tempwh);
      ret_code = 1;
    }
    break;
  case SYN_FUN:;
    char *fun_name = SYN_VALUE(child_at(0, child_at(0, node))->value)->name;
    if (IS_BUILTIN(fun_name)) {
      if (strcmp(fun_name, BUILTIN_WRITE) == 0 ||
          strcmp(fun_name, BUILTIN_WRITELN) == 0) {
        depth_pos(__get_exp_code, child_at(1, node), value, NULL, NULL);
        printf("pop $%lu\n", *temp);
        if (child_at(1, node)->children->size == 1 &&
            strcmp(SYN_VALUE(child_at(1, node)->value)->name, TOK_ID) == 0) {
          int idxs[] = {1, 0, -1};
          char *varname = SYN_VALUE(navigate(idxs, node)->value)->name;
          size_t idx = __get_declr_index(varname, data.curfun, data.context);
          if (idx > 0) {
            printf("%s $%lu, *$%lu\n", tac_op_string(OP_ASSIGN), *temp, *temp);
          }
        }
        printf("print%s $%lu\n",
               strcmp(fun_name, BUILTIN_WRITELN) == 0 ? "ln" : "", *temp);
      } else {
        printf("built-in: %s\n", fun_name);
      }
      ret_code = 1;
      break;
    }
  case SYN_EXP_COMP:
  case SYN_EXP:
    if (node->parent != NULL && node->parent->parent != NULL &&
        (strcmp(SYN_VALUE(node->parent->parent->value)->name, TOK_DECLR_FN) !=
             0 ||
         child_at(1, node->parent->parent) != node->parent) &&
        strcmp(SYN_VALUE(node->parent->parent->value)->name, TOK_DECLR) != 0) {
      depth_pos(__get_exp_code, node, value, NULL, NULL);
      /* adicionar code à árvore */
      ret_code = 1;
    }
    break;
  default:
    break;
  }
  return ret_code;
}

int __get_exp_code(node_t node, void *value) {
  t9n_data_t data = *((t9n_data_t *)value);
  size_t *temp = data.temps->last->value;
  node_t op = NULL, exp = NULL;
  if (SYN_VALUE(node->value)->type != SYN_FUN) {
    switch (node->children->size) {
    case 0:
      // printf("%s -> %s\n", SYN_VALUE(node->parent->value)->name,
      //        SYN_VALUE(node->value)->name);
      if (SYN_VALUE(node->value)->type != SYN_OP) {
        char *token = SYN_VALUE(node->parent->value)->name;
        if (strcmp(token, TOK_ID) == 0) {
          char *varname = SYN_VALUE(node->value)->name;
          CTX_fun_t fun = CTX_FUN(lookup_symbol(data.curfun, data.context));
          CTX_sym_t sym = lookup_symbol(varname, fun->context);
          size_t idx = __get_declr_index(varname, data.curfun, data.context);
          if (sym != NULL && sym->type == CTX_VAR) {
            if (idx-- > 0) {
              printf("push $%lu // %s\n", idx, varname);
            } else {
              int idx = indexOf(sym, fun->params);
              printf("push #%d // %s\n", idx, varname);
            }
          }
        } else {
          int cast = SYN_EXP(node->value)->cast;
          SYN_EXP(node->value)->cast = CTX_INV;
          switch (cast) {
          case CTX_CHAR:
            SYN_VALUE(node->parent->value)->name = TOK_CHAR;
            char *name = SYN_VALUE(node->value)->name;
            int val = atoi(name);
            /* Diminuindo, deve dar certo */
            name = (char *)realloc(name, sizeof(char) * 2);
            name[0] = val;
            name[1] = '\0';
            break;
          case CTX_INT:
            SYN_VALUE(node->parent->value)->name = TOK_INT;
            /* Um tamanho grande absurdo */
            char *intval = (char *)calloc(512, sizeof(char));
            switch (SYN_EXP(node->value)->data_type) {
            case CTX_CHAR:
              sprintf(intval, "%d", *SYN_EXP(node->value)->name);
              break;
            case CTX_FLOAT:;
              int dval = atoi(SYN_EXP(node->value)->name);
              sprintf(intval, "%d", dval);
              break;
            default:
              fprintf(stderr, "Invalid cast type in __get_exp_code(): %d\n",
                      SYN_EXP(node->value)->data_type);
              exit(EXIT_FAILURE);
            }
            free(SYN_EXP(node->value)->name);
            SYN_EXP(node->value)->name = intval;
            break;
          case CTX_FLOAT:
            SYN_VALUE(node->parent->value)->name = TOK_FLOAT;
            /* Um tamanho grande absurdo */
            char *floatval = (char *)calloc(512, sizeof(char));
            switch (SYN_EXP(node->value)->data_type) {
            case CTX_CHAR:
              sprintf(floatval, "%f", (float)*SYN_EXP(node->value)->name);
              break;
            case CTX_INT:;
              float fval = atof(SYN_EXP(node->value)->name);
              sprintf(floatval, "%f", fval);
              break;
            default:
              fprintf(stderr, "Invalid cast type in __get_exp_code(): %d\n",
                      SYN_EXP(node->value)->data_type);
              exit(EXIT_FAILURE);
            }
            free(SYN_EXP(node->value)->name);
            SYN_EXP(node->value)->name = floatval;
            break;
          default:
            break;
          }
          token = SYN_VALUE(node->parent->value)->name;
          int is_char = strcmp(token, TOK_CHAR) == 0;
          printf("push %s%s%s\n", is_char ? "'" : "",
                 SYN_VALUE(node->value)->name, is_char ? "'" : "");
        }
      }
      break;
    case 1:;
      break; /* TODO: ignorar? */
    case 2:  /* como fazer id++ e id--? */
      printf("// --> Aqui <--\n");
      printf("// %s\n", SYN_VALUE(child_at(0, node)->value)->name);
      printf("// %s\n", SYN_VALUE(child_at(1, node)->value)->name);
      int idxs[] = {0, 0, -1};
      if (SYN_VALUE(navigate(idxs, node)->value)->type == SYN_OP) {
        op = navigate(idxs, node);
        (*idxs)++;
        exp = navigate(idxs, node);
      } else {
        exp = navigate(idxs, node);
        (*idxs)++;
        op = navigate(idxs, node);
      }
      printf("// op: %s\n", SYN_VALUE(op->value)->name);
      printf("// exp: %s\n", SYN_VALUE(exp->value)->name);
      printf("pop $%lu\n", *temp);
      break;
    case 3:;
      op = child_at(0, child_at(1, node));
      switch (SYN_OP(op->value)->op_type) {
      case OP_BIN_GT:
      case OP_BIN_GTE:
        printf("pop $%lu\n", *temp);
        printf("pop $%lu\n", *temp + 1);
        break;
      default:
        printf("pop $%lu\n", *temp + 1);
        printf("pop $%lu\n", *temp);
        break;
      }
      __translate_bin_exp(op, &data);
      // printf("%s $0, $0, $1\n", SYN_VALUE(op->value)->name);
      printf("push $%lu\n\n", *temp);
      /* Ver o operador */
      break;
    case 5:
    default:
      break;
    }
  }
  if (strcmp(SYN_VALUE(node->parent->value)->name, TOK_FN) == 0 &&
      child_at(node->parent->children->size - 1, node->parent) == node &&
      !IS_BUILTIN(
          SYN_VALUE(child_at(0, child_at(0, node->parent))->value)->name)) {
    char *varname =
        SYN_VALUE(child_at(0, child_at(0, node->parent))->value)->name;
    size_t argcount = node->parent->children->size;
    if (argcount > 1) {
      node_t fn = node->parent;
      printf("// %s args\n", varname);
      MAP(
          if (MAP_i > 0) {
            printf("pop $%lu\n", *temp);
            printf("param $%lu\n", *temp);
          },
          fn->children);
    }
    printf("call %s", varname);
    if (argcount > 1) {
      printf(", %lu", argcount - 1);
    }
    printf("\n");
  }
  return 0;
}

const char *tac_op_string(int type) {
  switch (type) {
  case OP_ASSIGN:
    return "mov";
  // case OP_TER_FIRST:
  // case OP_TER_LAST:
  case OP_BIN_OR:
    return "or";
  case OP_BIN_AND:
    return "and";
  case OP_BIN_BIT_OR:
    return "bor";
  case OP_BIN_BIT_AND:
    return "band";
  case OP_BIN_XOR:
    return "bxor";
  case OP_BIN_NEQ:
  case OP_BIN_EQ:
    return "seq";
  case OP_BIN_GT:
  case OP_BIN_LT:
    return "slt";
  case OP_BIN_GTE:
  case OP_BIN_LTE:
    return "sleq";
  case OP_BIN_SHIFT_L:
    return "shl";
  case OP_BIN_SHIFT_R:
    return "shr";
  // case OP_BIN_IN:
  case OP_PLUS:
    return "add";
  case OP_MINUS:
    return "sub";
  case OP_STAR:
    return "mul";
  case OP_DIV:
    return "div";
  case OP_MOD:
    return "mod";
  // case OP_UNI_INC:
  // case OP_UNI_DEC:
  // case OP_UNI_REF:
  case OP_UNI_NEG:
    return "not";
  case OP_UNI_BIT_NEG:
    return "bnot";
  // case OP_POS_INC:
  // case OP_POS_DEC:
  default:
    fprintf(stderr, "Invalide operator type in tac_op_string()\n");
    exit(EXIT_FAILURE);
  }
}

void __translate_bin_exp(node_t op, t9n_data_t *data) {
  SYN_op_t syn = op->value;
  size_t temp = *((size_t *)data->temps->last->value);
  char *varname1 =
      SYN_VALUE(child_at(0, child_at(0, op->parent->parent))->value)->name;
  char *varname2 =
      SYN_VALUE(child_at(0, child_at(2, op->parent->parent))->value)->name;
  size_t idx1 = __get_declr_index(varname1, data->curfun, data->context);
  size_t idx2 = __get_declr_index(varname2, data->curfun, data->context);
  size_t aux;
  switch (syn->op_type) {
  case OP_ASSIGN:
    if (idx2 > 0) {
      printf("%s $%lu, *$%lu\n", tac_op_string(OP_ASSIGN), temp + 1, temp + 1);
    }
    __translate_cast(child_at(2, op->parent->parent), data);
    if (idx1 > 0) {
      printf("%s %s$%lu, $%lu\n", tac_op_string(syn->op_type),
             idx1 > 0 ? "*" : "", temp, temp + 1);
    }
    printf("%s $%lu, $%lu\n", tac_op_string(syn->op_type), temp, temp + 1);
    break;
  case OP_BIN_GT:
  case OP_BIN_GTE:
    aux = idx1;
    idx1 = idx2;
    idx2 = aux;
  case OP_BIN_OR:
  case OP_BIN_AND:
  case OP_BIN_BIT_OR:
  case OP_BIN_BIT_AND:
  case OP_BIN_XOR:
  case OP_BIN_EQ:
  case OP_BIN_NEQ:
  case OP_BIN_LT:
  case OP_BIN_LTE:
  case OP_BIN_SHIFT_L:
  case OP_BIN_SHIFT_R:
  case OP_PLUS:
  case OP_MINUS:
  case OP_STAR:
  case OP_DIV:
  case OP_MOD:
    if (idx2 > 0) {
      printf("%s $%lu, *$%lu\n", tac_op_string(OP_ASSIGN), temp + 1, temp + 1);
    }
    __translate_cast(child_at(0, child_at(2, op->parent->parent)), data);
    if (idx1 > 0) {
      printf("%s $%lu, *$%lu\n", tac_op_string(OP_ASSIGN), temp, temp);
    }
    __translate_cast(child_at(0, child_at(0, op->parent->parent)), data);
    printf("%s $%lu, $%lu, $%lu\n", tac_op_string(syn->op_type), temp, temp,
           temp + 1);
    if (syn->op_type == OP_BIN_NEQ) {
      printf("%s $%lu, $%lu\n", tac_op_string(OP_UNI_NEG), temp, temp);
    }
    break;
  case OP_BIN_IN:
    printf("in\n");
    break;
  default:
    fprintf(stderr, "Invalid operator in __translate_bin_exp(): %s\n",
            operator_string(syn->op_type));
    exit(EXIT_FAILURE);
  }
}

void __translate_cast(node_t node, t9n_data_t *data) {
  size_t temp = *((size_t *)data->temps->last->value);
  while (SYN_VALUE(node->value)->type != SYN_EXP &&
         SYN_VALUE(node->value)->type != SYN_EXP_COMP) {
    node = child_at(0, node);
  }
  SYN_exp_t exp = node->value;
  if (exp->cast != CTX_INV) {
    switch (exp->data_type) {
    case CTX_CHAR:
      printf("chto");
      break;
    case CTX_INT:
      printf("intto");
      break;
    case CTX_FLOAT:
      printf("flto");
      break;
    default:
      break;
    }
    switch (exp->cast) {
    case CTX_CHAR:
      printf("ch");
      break;
    case CTX_INT:
      printf("int");
      break;
    case CTX_FLOAT:
      printf("fl");
      break;
    default:
      break;
    }
    printf(" $%lu, $%lu\n", temp + 1, temp + 1);
  }
}

CTX_sym_t get_symbol_identifier(char *name, char *id, node_t context) {
  CTX_sym_t sym = NULL;
  char *data[2] = {name, id};
  depth_pre(__get_symbol_identifier, context, data, NULL, NULL);
  return sym;
}

int __get_symbol_identifier(node_t node, void *data) {
  char *name = ((char **)data)[0];
  char *id = ((char **)data)[1];
  size_t l = level(node);
  if (*id == '\0' || id[strlen(id) - 1] != l + '0') {
    char suf[2] = {l + '0', '\0'};
    strcat(id, suf);
  }
  if (has_symbol(name, node->value)) {

    return 1;
  }
  return 0;
}

size_t __get_declr_index(char *id, char *curfun, node_t context) {
  size_t idx = 0;
  CTX_fun_t fun = CTX_FUN(lookup_symbol(curfun, context));
  CTX_sym_t var = lookup_symbol(id, fun->context);
  if (var != NULL && (fun->params == NULL || indexOf(var, fun->params) < 0)) {
    MAP(
        {
          idx++;
          if (strcmp(CTX_SYM(MAP_val)->id, id) == 0) {
            break;
          }
        },
        fun->context->value);
  }
  return idx;
}
