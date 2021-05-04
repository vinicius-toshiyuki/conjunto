#include <context.h>
#include <list.h>
#include <stddef.h>
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
  create_table(tree);
  create_code(tree, context);
}

void create_table(node_t tree) {
  depth_pos(__create_table, tree, NULL, __create_table_header, NULL);
}

void __create_table_header() { printf(".table\n"); }

int __create_table(node_t node, void *data) {
  if (node->parent != NULL) {
    SYN_value_t syn = node->value;
    if (strcmp(syn->name, TOK_STRING) == 0) {
      char *string = unscape(SYN_VALUE(child_at(0, node)->value)->name);
      char suffix[512] = {'\0'};
      while (node->parent != NULL) {
        int idx = indexOf(node, node->parent->children);
        size_t sufend = strlen(suffix);
        sprintf(suffix + sufend, "%d", idx);
        node = node->parent;
      }
      printf("char s%s[] = \"%s\"\n", suffix, string);
      free(string);
    }
  }
  return 0;
}

void create_code(node_t tree, node_t context) {
  t9n_data_t data = {context, create_list(), NULL, create_list()};
  append(calloc(1, sizeof(size_t)), data.temps);
  depth_pre(__create_code, tree, &data, __create_code_header, NULL);
  printf("EOF:\n");
  printf("nop\n");
  for_each(free_list, data.temps);
  delete_list(data.temps);
  for_each(free_list, data.loops);
  delete_list(data.loops);
}
void __create_code_header() {
  printf(".code\n");
  /* int write(val) */
  printf(BUILTIN_WRITE ":\n");
  printf("seq $0, #1, 0\n");
  printf("brz STRING, $0\n"); /* Não string */
  printf("print #0\n");
  printf("jump ENDWRT\n");
  printf("STRING:\n");   /* String */
  printf("mov $0, 0\n"); /* $0 = index */
  printf("STARTSTR:\n");
  printf("mov $1, #0[$0]\n"); /* $1 = string[index] */
  printf("mov $2, '\\0'\n");
  printf("seq $2, $2, $1\n"); /* string[index] == '\0' */
  printf("brnz ENDWRT, $2\n");
  printf("print $1\n");      /* print string[index] */
  printf("add $0, $0, 1\n"); /* index++ */
  printf("jump STARTSTR\n");
  printf("ENDWRT:\n");
  printf("return 0\n");
  /* int writeln(val) */
  printf(BUILTIN_WRITELN ":\n");
  printf("param #0\n");
  printf("param #1\n");
  printf("call " BUILTIN_WRITE ", 2\n");
  printf("println\n");
  printf("return 0\n");
  /* int read(var) */
  printf(BUILTIN_READ ":\n");
  printf("mov $0, *#0\n"); /* $0 = data type */
  printf("seq $1, $0, %d\n", CTX_CHAR);
  printf("brz READ_INT, $1\n");
  printf("scanc $1\n");
  printf("mov #0[1], $1\n");
  printf("jump READ_END\n");
  printf("READ_INT:\n");
  printf("scani $1\n");
  printf("mov #0[1], $1\n");
  printf("seq $1, $0, %d\n", CTX_INT);
  printf("brz READ_FLOAT, $1\n");
  printf("jump READ_END\n");
  printf("READ_FLOAT:\n");
  printf("scanf $1\n");
  printf("mov #0[1], $1\n");
  printf("seq $1, $0, %d\n", CTX_FLOAT);
  printf("READ_END:\n");
  printf("return 0\n");
  /* int is_set(set) */
  printf(BUILTIN_ISSET ":\n");
  printf("mov $0, *#0\n");
  printf("seq $0, $0, %d\n", CTX_SET);
  printf("return $0\n");
  /* set add(val, tgt) */
  /* TODO: como checar dois sets? */
  // printf(BUILTIN_ADD ":\n");
  // printf("mov $0, *#0\n");   /* data type */
  // printf("mov $1, #1[1]\n"); /* set length */
  // printf("mov $2, 0\n");     /* index */
  // printf("mov $3, 0\n");     /* has_val */
  // printf("ADD_CHECK:\n");
  // printf("brnz ADD_CHECK_END, $3\n");
  // printf("seq $4, $2, $1\n");
  // printf("brz ADD_CHECK_END, $4\n"); /* branch on index == set length */
  // printf("mul $4, $2, 2\n");         /* tempidx = index * 2 */
  // printf("add $4, $4, 2\n");         /* tempidx += 2 */

  // printf("mov $5, #1[$4]\n");
  // printf("seq $5, $0, $5\n");
  // printf("brnz ADD_CHECKED, $5\n");
  // printf("add $4, $4, 1\n"); /* tempidx++ */

  // printf("seq $5, $0, %d\n", CTX_SET);
  // printf("brnz ADD_SET, $5\n"); /* if type == set */

  // printf("mov $5, #1[$4]\n"); /* set[tempidx] */
  // printf("mov $6, #0[1]\n");  /* val[1] */
  // printf("seq $3, $5, $6\n");
  // printf("jump ADD_CHECKED\n");
  // printf("ADD_SET:\n");
  // /* TODO: como checar? */

  // printf("ADD_CHECKED:\n");
  // printf("add $2, $2, 1\n"); /* index++ */
  // printf("jump ADD_CHECK\n");
  // printf("ADD_CHECK_END:\n");

  // /************** COPIA O SET **************/
  // printf("return 0\n");
}

int __create_code(node_t node, void *value) {
  static size_t ifcount = 0, loopcount = 0;
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
      depth_pre(__create_code, node->children->last->value, value, NULL, NULL);
      printf("return 0\n");
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_DECLR) == 0) {
      MAP(
          if (MAP_i > 0) {
            char *varname = SYN_VALUE(child_at(0, MAP_val)->value)->name;
            size_t idx = __get_declr_index(varname, data.curfun, data.context);
            if (idx > 0) {
              char *type =
                  SYN_VALUE(child_at(0, child_at(0, node))->value)->name;
              printf("// %s %s\n", type, varname);
              printf("mema $%lu, 2\n", *temp);
              printf("mov *$%lu, %d\n", (*temp)++, data_type_code(type));
            }
          },
          node->children);
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_RETURN) == 0) {
      printf("// return exp\n");

      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);

      if (strcmp(data.curfun, FUN_MAIN) == 0) {
        printf("jump EOF\n");
      } else {
        printf("return $%lu\n", *temp);
      }
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
      size_t *temploop = (size_t *)malloc(sizeof(size_t));
      *temploop = loopcount++;
      append(temploop, data.loops);
      printf("LOOP_%lu:\n", *temploop);
      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz LOOP_END_%lu, $%lu\n", *temploop, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("jump LOOP_%lu\n", *temploop);
      printf("LOOP_END_%lu:\n", *temploop);
      free(removeAt(data.loops->size - 1, data.loops));
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_FOR) == 0) {
      size_t *temploop = (size_t *)malloc(sizeof(size_t));
      *temploop = loopcount++;
      append(temploop, data.loops);
      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("LOOP_%lu:\n", *temploop);
      depth_pos(__get_exp_code, child_at(1, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz LOOP_END_%lu, $%lu\n", *temploop, *temp);
      depth_pre(__create_code, child_at(3, node), value, NULL, NULL);
      depth_pos(__get_exp_code, child_at(2, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("jump LOOP_%lu\n", *temploop);
      printf("LOOP_END_%lu:\n", *temploop);
      free(removeAt(data.loops->size - 1, data.loops));
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_BREAK) == 0) {
      printf("jump LOOP_END_%lu\n", *((size_t *)data.loops->last->value));
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
        size_t print_mode = 0;
        if (child_at(1, node)->children->size == 1) {
          if (strcmp(SYN_VALUE(child_at(1, node)->value)->name, TOK_ID) == 0) {
            int idxs[] = {1, 0, -1};
            char *varname = SYN_VALUE(navigate(idxs, node)->value)->name;
            size_t idx = __get_declr_index(varname, data.curfun, data.context);
            if (idx > 0) {
              printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), *temp,
                     idx - 1); /* Obtém o valor da variável */
            }
          } else if (strcmp(SYN_VALUE(child_at(1, node)->value)->name,
                            TOK_STRING) == 0) {
            print_mode = 1;
          }
        }
        printf("param $%lu\n", *temp);
        printf("param %lu\n", print_mode);
        printf("call write%s, 2\n",
               strcmp(fun_name, BUILTIN_WRITELN) == 0 ? "ln" : "");
      } else if (strcmp(fun_name, BUILTIN_READ) == 0) {
        int idxs[] = {1, 0, -1};
        char *varname = SYN_VALUE(navigate(idxs, node)->value)->name;
        size_t idx = __get_declr_index(varname, data.curfun, data.context);
        printf("param $%lu\n", idx - 1);
        printf("call read, 1\n");
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
  node_t op = NULL;
  if (SYN_VALUE(node->value)->type != SYN_FUN) {
    switch (node->children->size) {
    case 0:
      // printf("%s -> %s\n", SYN_VALUE(node->parent->value)->name,
      //        SYN_VALUE(node->value)->name);
      if (strcmp(SYN_VALUE(node->value)->name, TOK_EMPTYEXP) == 0) {
        printf("push 1\n");
      } else if (strcmp(SYN_VALUE(node->parent->value)->name, TOK_STRING) ==
                 0) {
        /* TODO: parar de repetir esse cdigo */
        char suffix[512] = {'\0'};
        node_t aux = node->parent;
        while (aux->parent != NULL) {
          int idx = indexOf(aux, aux->parent->children);
          size_t sufend = strlen(suffix);
          sprintf(suffix + sufend, "%d", idx);
          aux = aux->parent;
        }
        printf("%s $%lu, &s%s\n", tac_op_string(OP_ASSIGN), *temp, suffix);
        printf("push $%lu\n", *temp);
      } else if (SYN_VALUE(node->value)->type != SYN_OP) {
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
    case 2:; /* como fazer id++ e id--? */
      int idxs[] = {0, 0, -1};
      if (SYN_VALUE(navigate(idxs, node)->value)->type == SYN_OP) {
        op = navigate(idxs, node);
        (*idxs)++;
        // exp = navigate(idxs, node);
      } else {
        // exp = navigate(idxs, node);
        (*idxs)++;
        op = navigate(idxs, node);
      }
      printf("pop $%lu\n", *temp);
      __translate_uni_exp(op, &data);
      printf("push $%lu\n\n", *temp);
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
  case OP_POS_INC:
  case OP_UNI_INC:
  case OP_PLUS:
    return "add";
  case OP_POS_DEC:
  case OP_UNI_DEC:
  case OP_MINUS:
    return "sub";
  case OP_STAR:
    return "mul";
  case OP_DIV:
    return "div";
  case OP_MOD:
    return "mod";
  // case OP_UNI_REF:
  case OP_UNI_NEG:
    return "not";
  case OP_UNI_BIT_NEG:
    return "bnot";
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
      printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp + 1,
             temp + 1);
    }
    __translate_cast(child_at(2, op->parent->parent), data);
    if (idx1 > 0) {
      printf("%s $%lu%s, $%lu\n", tac_op_string(syn->op_type), temp,
             idx1 > 0 ? "[1]" : "", temp + 1);
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
      printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp + 1,
             temp + 1);
    }
    __translate_cast(child_at(0, child_at(2, op->parent->parent)), data);
    if (idx1 > 0) {
      printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, temp);
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

void __translate_uni_exp(node_t op, t9n_data_t *data) {
  SYN_op_t syn = op->value;
  size_t temp = *((size_t *)data->temps->last->value);
  char *varname = NULL;
  if (child_at(0, op->parent->parent) != op->parent) {
    varname =
        SYN_VALUE(child_at(0, child_at(0, op->parent->parent))->value)->name;
  } else {
    varname =
        SYN_VALUE(child_at(0, child_at(1, op->parent->parent))->value)->name;
  }
  size_t idx = __get_declr_index(varname, data->curfun, data->context);
  if (idx > 0) {
    printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, temp);
  }
  switch (syn->op_type) {
  case OP_UNI_INC:
  case OP_UNI_DEC:
    printf("%s $%lu, $%lu, 1\n", tac_op_string(syn->op_type), temp, temp);
    printf("%s $%lu[1], $%lu\n", tac_op_string(OP_ASSIGN), idx - 1, temp);
    break;
  // case OP_UNI_REF:
  case OP_MINUS:
    printf("minus $%lu, $%lu\n", temp, temp);
    break;
  case OP_UNI_BIT_NEG:
    printf("%s $%lu, $%lu, 1\n", tac_op_string(syn->op_type), temp, temp);
    break;
  case OP_POS_INC:
  case OP_POS_DEC:
    printf("// pos\n");
    printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, idx - 1);
    printf("%s $%lu, $%lu, 1\n", tac_op_string(syn->op_type), temp + 1, temp);
    printf("%s $%lu[1], $%lu\n", tac_op_string(OP_ASSIGN), idx - 1, temp + 1);
    break;
  default:
    fprintf(stderr, "Invalid operator in __translate_uni_exp(): %s\n",
            operator_string(syn->op_type));
    exit(EXIT_FAILURE);
  }
}

void __translate_cast(node_t node, t9n_data_t *data) {
  size_t temp = *((size_t *)data->temps->last->value);
  while (SYN_VALUE(node->value)->type != SYN_EXP &&
         SYN_VALUE(node->value)->type != SYN_EXP_COMP) {
    if (node->children->size == 0) {
      return;
    }
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
