#include <builtin.h>
#include <context.h>
#include <eval.h>
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
  create_table(tree);
  create_code(tree, context);
}

void create_table(node_t tree) {
  depth_pos(__create_table, tree, NULL, __create_table_header, NULL);
}

void __create_table_header() {
  printf(".table\n");
  printf("int empty[] = {%d, 0}\n", CTX_SET);
}

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
  *((int *)data.temps->last->value) = 1;
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
  get_var_code();
  set_var_code();
  set_cmp_code();
  in_code();
  is_set_code();
  write_code();
  writeln_code();
  read_code();
  add_code();
  exists_code();
  remove_code();
}

int __create_code(node_t node, void *value) {
  static size_t ifcount = 0, loopcount = 0;
  t9n_data_t *data = value;
  int ret_code = 1;
  SYN_value_t syn = node->value;
  size_t *temp = data->temps->last->value;
  switch (syn->type) {
  case SYN_TAG:
    if (strcmp(syn->name, TOK_DECLR_FN) == 0) {
      data->curfun = SYN_VALUE(child_at(0, child_at(1, node))->value)->name;
      CTX_fun_t fun = CTX_FUN(lookup_symbol(data->curfun, data->context));
      data->context = fun->context;
      append(calloc(1, sizeof(size_t)), data->temps);
      *((int *)data->temps->last->value) = 1;
      char suffix[512];
      __get_fun_suffix(data->curfun, data->context, suffix);
      printf("%s%s:\n", data->curfun, suffix);
      printf("mema $0, 3 // elem casts\n");
      depth_pre(__create_code, node->children->last->value, value, NULL, NULL);
    } else if (strcmp(syn->name, TOK_DECLR) == 0) {
      MAP(
          if (MAP_i > 0) {
            char *varname = SYN_VALUE(child_at(0, MAP_val)->value)->name;
            char *type = SYN_VALUE(child_at(0, child_at(0, node))->value)->name;
            printf("// %s %s\n", type, varname);
            int type_code = data_type_code(type);
            if (type_code == CTX_SET) {
              printf("mema $%lu, %d\n", *temp, 3);
              printf("mema $%lu, 0\n", *temp + 1);
              printf("mov $%lu[2], $%lu\n", *temp, *temp + 1);
            } else if (type_code == CTX_ELEM) {
              printf("mema $%lu, %d\n", *temp, 3);
              /* el.sec_type = CTX_UNK */
              printf("mov $%lu[2], %d\n", *temp, CTX_UNK);
            } else {
              printf("mema $%lu, %d\n", *temp, 2);
            }
            printf("mov *$%lu, %d\n", (*temp)++, data_type_code(type));
          },
          node->children);
    } else if (strcmp(syn->name, TOK_RETURN) == 0) {
      printf("// return exp\n");

      depth_pre(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      if (strcmp(SYN_VALUE(child_at(0, node)->value)->name, TOK_ID) == 0) {
        printf("param $%lu\n", *temp);
        printf("param $0\n");
        printf("call get_var, 2\n");
        printf("pop $%lu\n", *temp);
      }

      if (strcmp(data->curfun, FUN_MAIN) == 0) {
        printf("jump EOF\n");
      } else {
        printf("return $%lu\n", *temp);
      }
    } else if (strcmp(syn->name, TOK_IF) == 0) {
      size_t tempif = ifcount++;
      depth_pre(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz IF_%lu, $%lu\n", tempif, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("IF_%lu:\n", tempif);
    } else if (strcmp(syn->name, TOK_IF_ELSE) == 0) {
      size_t tempif = ifcount++;
      depth_pre(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz IF_%lu, $%lu\n", tempif, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("jump ELSE_%lu\n", tempif);
      printf("IF_%lu:\n", tempif);
      depth_pre(__create_code, child_at(2, node), value, NULL, NULL);
      printf("ELSE_%lu:\n", tempif);
    } else if (strcmp(syn->name, TOK_WHILE) == 0) {
      size_t *temploop = (size_t *)malloc(sizeof(size_t));
      *temploop = loopcount++;
      append(temploop, data->loops);
      printf("LOOP_%lu:\n", *temploop);
      depth_pre(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz LOOP_END_%lu, $%lu\n", *temploop, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("jump LOOP_%lu\n", *temploop);
      printf("LOOP_END_%lu:\n", *temploop);
      free(removeAt(data->loops->size - 1, data->loops));
    } else if (strcmp(syn->name, TOK_FOR) == 0) {
      size_t *temploop = (size_t *)malloc(sizeof(size_t));
      *temploop = loopcount++;
      append(temploop, data->loops);
      depth_pre(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("LOOP_%lu:\n", *temploop);
      depth_pre(__get_exp_code, child_at(1, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz LOOP_END_%lu, $%lu\n", *temploop, *temp);
      depth_pre(__create_code, child_at(3, node), value, NULL, NULL);
      depth_pre(__get_exp_code, child_at(2, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("jump LOOP_%lu\n", *temploop);
      printf("LOOP_END_%lu:\n", *temploop);
      free(removeAt(data->loops->size - 1, data->loops));
    } else if (strcmp(syn->name, TOK_FORALL) == 0) {
      size_t *temploop = (size_t *)malloc(sizeof(size_t));
      *temploop = loopcount++;
      append(temploop, data->loops);

      node_t inexp = child_at(0, node);
      int idxs[] = {0, 0, -1};
      char *varname = SYN_VALUE(navigate(idxs, inexp)->value)->name;
      char idxpref = '$';
      size_t idx = __get_declr_index(varname, data->curfun, data->context);
      if (idx == 0) {
        idxpref = '#';
        idx = __get_par_index(varname, data->curfun, data->context) - 1;
      }
      /* Obtém o código do set */
      depth_pre(__get_exp_code, child_at(2, inexp), value, NULL, NULL);
      printf("pop $%lu // set\n", *temp);
      printf("mov $%lu, $%lu[1] // set.len\n", *temp + 1,
             *temp);                                   /* $1 = set.len  */
      printf("mov $%lu, 0\n", *temp + 2);              /* $2 = i */
      printf("mov $%lu, $%lu[2]\n", *temp + 3, *temp); /* $3 = set.data */
      printf("LOOP_%lu:\n", *temploop);
      printf("seq $%lu, $%lu, $%lu\n", *temp + 4, *temp + 2, *temp + 1);
      printf("brnz LOOP_END_%lu, $%lu\n", *temploop, *temp + 4);
      printf("mul $%lu, $%lu, 2\n", *temp + 4, *temp + 2); /* $4 = i * 2 */
      printf("mov $%lu, $%lu[$%lu]\n", *temp + 5, *temp + 3,
             *temp + 4); /* $5 = set.data[i].type */
      if (lookup_symbol(varname, data->context)->data_type == CTX_ELEM) {
        printf("mov %c%lu[2], $%lu\n", idxpref, idx,
               *temp + 5); /* var.sec_type = $5 */
      }
      printf("add $%lu, $%lu, 1\n", *temp + 4, *temp + 4); /* $4 += 1 */
      printf("mov $%lu, $%lu[$%lu]\n", *temp + 5, *temp + 3,
             *temp + 4); /* $5 = set.data[i].data */
      printf("mov %c%lu[1], $%lu\n", idxpref, idx,
             *temp + 5); /* var.data = $5 */

      size_t cur_temp = *temp;
      for (size_t i = 0; i < 6; i++) {
        printf("push $%lu\n", *temp + i);
      }
      // *temp += 6; /* $6 > podem ser apagados */
      printf("// -> forall start\n");
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("// -> forall end\n");
      *temp = cur_temp;
      for (size_t i = 0; i < 6; i++) {
        printf("pop $%lu\n", *temp + (5 - i));
      }
      // *temp -= 6;
      printf("add $%lu, $%lu, 1\n", *temp + 2, *temp + 2);
      printf("jump LOOP_%lu\n", *temploop);
      printf("LOOP_END_%lu:\n", *temploop);

      printf("// %s %lu\n", varname, idx);

      free(removeAt(data->loops->size - 1, data->loops));
    } else if (strcmp(syn->name, TOK_BLOCK) == 0 &&
               strcmp(SYN_VALUE(node->parent->value)->name, TOK_DECLR_FN) !=
                   0) {
      size_t blkidx = 0;
      MAP(
          {
            if (MAP_val == node) {
              break;
            }
            char *node_name = SYN_VALUE(((node_t)MAP_val)->value)->name;
            if (strcmp(node_name, TOK_BLOCK) == 0 ||
                strcmp(node_name, TOK_DECLR_FN) == 0) {
              blkidx++;
            }
          },
          node->parent->children);
      data->context = child_at(blkidx, data->context);
      MAP(depth_pre(__create_code, MAP_val, value, NULL, NULL), node->children);

      data->context = data->context->parent;
    } else if (strcmp(syn->name, TOK_BREAK) == 0) {
      printf("jump LOOP_END_%lu\n", *((size_t *)data->loops->last->value));
    }
    break;
  case SYN_FUN:;
  case SYN_EXP_COMP:
  case SYN_EXP:
    if (node->parent != NULL && node->parent->parent != NULL &&
        (strcmp(SYN_VALUE(node->parent->parent->value)->name, TOK_DECLR_FN) !=
             0 ||
         child_at(1, node->parent->parent) != node->parent) &&
        strcmp(SYN_VALUE(node->parent->parent->value)->name, TOK_DECLR) != 0) {
      depth_pre(__get_exp_code, node, value, NULL, NULL);
      printf("pop $%lu\n", *temp);
    }
    break;
  default:
    ret_code = 0;
    break;
  }
  return ret_code;
}

int __get_exp_code(node_t node, void *value) {
  static size_t wrtcall = 0;
  int ret_code = 0;
  t9n_data_t *data = value;
  size_t *temp = data->temps->last->value;
  node_t op = NULL, exp = NULL;
  if (SYN_VALUE(node->value)->type != SYN_FUN) {
    switch (node->children->size) {
    case 0:
      if (strcmp(SYN_VALUE(node->value)->name, TOK_EMPTYEXP) == 0) {
        printf("push 1\n");
      } else if (strcmp(SYN_VALUE(node->parent->value)->name, TOK_STRING) ==
                 0) {
        char suffix[512] = {'\0'};
        node_t aux = node->parent;
        while (aux->parent != NULL) {
          int idx = indexOf(aux, aux->parent->children);
          size_t sufend = strlen(suffix);
          sprintf(suffix + sufend, "%d", idx);
          aux = aux->parent;
        }
        char *unscaped = unscape(SYN_VALUE(node->value)->name);
        printf("%s $%lu, &s%s // \"%s\"\n", tac_op_string(OP_ASSIGN), *temp,
               suffix, unscaped);
        free(unscaped);
        printf("push $%lu\n", *temp);
      } else if (SYN_VALUE(node->value)->type != SYN_OP) {
        char *token = SYN_VALUE(node->parent->value)->name;
        if (strcmp(token, TOK_ID) == 0) {
          char *varname = SYN_VALUE(node->value)->name;
          CTX_sym_t sym = lookup_symbol(varname, data->context);
          if (sym->type != CTX_FUN) {
            char idxpref = '$';
            size_t idx =
                __get_declr_index(varname, data->curfun, data->context);
            if (idx == 0) {
              idxpref = '#';
              idx = __get_par_index(varname, data->curfun, data->context) - 1;
            }
            // printf("param %c%lu\n", idxpref, idx);
            // printf("param $0\n");
            // printf("call get_var, 2\n");
            printf("push %c%lu // %s\n", idxpref, idx, varname);
          }
        } else if (strcmp(token, TOK_EMPTY) == 0) {
          printf("%s $%lu, &empty\n", tac_op_string(OP_ASSIGN), *temp);
          printf("push $%lu\n", *temp);
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
        exp = navigate(idxs, node);
      } else {
        exp = navigate(idxs, node);
        (*idxs)++;
        op = navigate(idxs, node);
      }
      depth_pre(__get_exp_code, exp, value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      __translate_uni_exp(op, data);
      printf("push $%lu\n\n", *temp);
      ret_code = 1;
      break;
    case 3:
      depth_pre(__get_exp_code, child_at(0, node), value, NULL, NULL);
      depth_pre(__get_exp_code, child_at(2, node), value, NULL, NULL);
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
      __translate_bin_exp(op, data);
      // printf("%s $0, $0, $1\n", SYN_VALUE(op->value)->name);
      if (SYN_OP(op->value)->op_type == OP_ASSIGN &&
          strcmp(SYN_VALUE(child_at(0, node)->value)->name, TOK_ID) == 0) {
        SYN_exp_t exp = child_at(0, child_at(0, node))->value;
        char *varname = exp->name;
        char idxpref = '$';
        size_t idx = __get_declr_index(varname, data->curfun, data->context);
        if (idx == 0) {
          idxpref = '#';
          idx = __get_par_index(varname, data->curfun, data->context) - 1;
        }
        CTX_sym_t sym = lookup_symbol(varname, data->context);
        if (strcmp(SYN_VALUE(child_at(2, node)->value)->name, TOK_EMPTY) != 0 &&
            sym->data_type == CTX_SET) {
          printf("mov %c%lu, $%lu\n", idxpref, idx, *temp);
        } else if (sym->data_type == CTX_ELEM) {
          printf("mov %c%lu[2], %d\n", idxpref, idx,
                 eval_exp_type(child_at(2, node)));
        }
      }
      printf("push $%lu\n", *temp);
      ret_code = 1;
      break;
    case 5:
    default:
      break;
    }
  } else {
    char *fun_name = SYN_VALUE(child_at(0, child_at(0, node))->value)->name;
    size_t argcount = node->children->size;
    if (!IS_BUILTIN(fun_name)) {
      if (argcount > 1) {
        node_t fn = node;
        MAP(
            if (MAP_i > 0) {
              depth_pre(__get_exp_code,
                        child_at(node->children->size - MAP_i, node), value,
                        NULL, NULL);
            },
            fn->children);
        printf("// %s args\n", fun_name);
        MAP(
            if (MAP_i > 0) {
              printf("pop $%lu\n", *temp + MAP_i - 1);
              if (strcmp(SYN_VALUE(child_at(MAP_i, node)->value)->name,
                         TOK_ID) != 0) {
                int exp_type = eval_exp_type(child_at(MAP_i, node));
                printf("mema $%lu, 2\n", *temp + MAP_i);
                printf("mov *$%lu, %d\n", *temp + MAP_i, exp_type);
                printf("mov $%lu[1], $%lu\n", *temp + MAP_i, *temp + MAP_i - 1);
                printf("mov $%lu, $%lu\n", *temp + MAP_i - 1, *temp + MAP_i);
              }
            },
            fn->children);
        MAP(
            if (MAP_i > 0) { printf("param $%lu\n", *temp + MAP_i - 1); },
            fn->children);
      }
      char suffix[512];
      __get_fun_suffix(fun_name, data->context, suffix);
      printf("call %s%s", fun_name, suffix);
      if (argcount > 1) {
        printf(", %lu", argcount - 1);
      }
      printf("\n");
      ret_code = 1;
    } else {
      if (strcmp(fun_name, BUILTIN_WRITE) == 0 ||
          strcmp(fun_name, BUILTIN_WRITELN) == 0) {
        depth_pre(__get_exp_code, child_at(1, node), value, NULL, NULL);
        printf("pop $%lu\n", *temp);
        printf("mov $%lu, 0 // print_mode\n", *temp + 1);
        // if (child_at(1, node)->children->size == 1) {
        if (strcmp(SYN_VALUE(child_at(1, node)->value)->name, TOK_ID) == 0) {
          int idxs[] = {1, 0, -1};
          char *varname = SYN_VALUE(navigate(idxs, node)->value)->name;
          char idxpref = '$';
          size_t idx = __get_declr_index(varname, data->curfun, data->context);
          if (idx == 0) {
            idxpref = '#';
            idx = __get_par_index(varname, data->curfun, data->context) - 1;
          }
          printf("param %c%lu // %s\n", idxpref, idx, varname);
          printf("param $0\n");
          printf("call get_var, 2\n");
          printf("pop $%lu\n", *temp);

          printf("mov $%lu, *%c%lu\n", *temp + 2, idxpref, idx);
          printf("WRT_CHEK_ELEM_SET_%lu:\n", wrtcall);
          printf("seq $%lu, $%lu, %d\n", *temp + 3, *temp + 2, CTX_SET);
          printf("brz WRT_CALL_NOT_SET_%lu, $%lu\n", wrtcall, *temp + 3);
          printf("mov $%lu, 2\n", *temp + 1);
          printf("jump WRT_CALL_DONE_%lu\n", wrtcall);
          printf("WRT_CALL_NOT_SET_%lu:\n", wrtcall);
          printf("seq $%lu, $%lu, %d\n", *temp + 3, *temp + 2, CTX_ELEM);
          printf("brz WRT_CALL_DONE_%lu, $%lu\n", wrtcall, *temp + 3);
          printf("mov $%lu, %c%lu[2]\n", *temp + 2, idxpref, idx);
          printf("jump WRT_CHEK_ELEM_SET_%lu\n", wrtcall);
          printf("WRT_CALL_DONE_%lu:\n", wrtcall++);
          // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), *temp,
          //        idx); /* Obtém o valor da variável */
        } else if (strcmp(SYN_VALUE(child_at(1, node)->value)->name,
                          TOK_STRING) == 0) {
          printf("mov $%lu, 1\n", *temp + 1);
        }
        // printf(">>> %s\n", data_type_string(eval_exp_type(child_at(1,
        // node))));
        // }
        printf("param $%lu\n", *temp);
        printf("param $%lu\n", *temp + 1);
        printf("call write%s, 2\n",
               strcmp(fun_name, BUILTIN_WRITELN) == 0 ? "ln" : "");
      } else if (strcmp(fun_name, BUILTIN_READ) == 0) {
        int idxs[] = {1, 0, -1};
        char *varname = SYN_VALUE(navigate(idxs, node)->value)->name;
        char idxpref = '$';
        size_t idx = __get_declr_index(varname, data->curfun, data->context);
        if (idx == 0) {
          idxpref = '#';
          idx = __get_par_index(varname, data->curfun, data->context) - 1;
        }
        printf("param %c%lu\n", idxpref, idx);
        printf("call read, 1\n");
      } else if (strcmp(fun_name, BUILTIN_ISSET) == 0) {
        if (strcmp(SYN_VALUE(child_at(1, node)->value)->name, TOK_ID) == 0) {
          char *varname =
              SYN_VALUE(child_at(0, child_at(1, node))->value)->name;
          char idxpref = '$';
          size_t idx = __get_declr_index(varname, data->curfun, data->context);
          if (idx == 0) {
            idxpref = '#';
            idx = __get_par_index(varname, data->curfun, data->context) - 1;
          }
          printf("param %c%lu\n", idxpref, idx);
          printf("call is_set, 1\n");
        } else {
          int exp_type = eval_exp_type(child_at(1, node));
          printf("// is_set(%s)\n", data_type_string(exp_type));
          printf("push %d\n", exp_type == CTX_SET ? 1 : 0);
        }
      } else if (strcmp(fun_name, BUILTIN_ADD) == 0) {
        node_t exp = child_at(1, node);
        int exp_type = eval_exp_type(child_at(0, exp));
        depth_pre(__get_exp_code, child_at(2, exp), value, NULL, NULL);
        depth_pre(__get_exp_code, child_at(0, exp), value, NULL, NULL);

        printf("pop $%lu // val\n", *temp);
        char idxpref = '$';
        size_t idx = 0;
        if (strcmp(SYN_VALUE(child_at(0, exp)->value)->name, TOK_ID) == 0) {
          int idxs[] = {0, 0, -1};
          char *varname = SYN_VALUE(navigate(idxs, exp)->value)->name;
          idx = __get_declr_index(varname, data->curfun, data->context);
          if (idx == 0) {
            idxpref = '#';
            idx = __get_par_index(varname, data->curfun, data->context) - 1;
          }
          printf("param %c%lu\n", idxpref, idx);
          printf("param $0\n");
          printf("call get_var, 2\n");
          printf("pop $%lu\n", *temp);
        }
        printf("pop $%lu // set\n", *temp + 1);

        if (exp_type != CTX_ELEM) {
          printf("param %d // type\n", exp_type);
        } else {
          printf("mov $%lu, %c%lu[2]\n", *temp + 2, idxpref, idx);
          printf("param $%lu\n", *temp + 2);
        }
        printf("param $%lu\n", *temp);
        printf("param $%lu\n", *temp + 1);
        printf("call set_" BUILTIN_ADD ", 3\n");
      } else if (strcmp(fun_name, BUILTIN_EXISTS) == 0) {
        node_t inexp = child_at(1, node);
        int idxs[] = {0, 0, -1};
        char *varname = SYN_VALUE(navigate(idxs, inexp)->value)->name;
        char idxpref = '$';
        size_t idx = __get_declr_index(varname, data->curfun, data->context);
        if (idx == 0) {
          idxpref = '#';
          idx = __get_par_index(varname, data->curfun, data->context) - 1;
        }
        // printf("id: %s, idx: %lu\n", varname, idx);
        depth_pre(__get_exp_code, child_at(2, inexp), value, NULL, NULL);
        printf("pop $%lu // set\n", *temp);
        printf("param %c%lu // val\n", idxpref, idx);
        printf("param $%lu\n", *temp);
        printf("call exists, 2\n");
      } else if (strcmp(fun_name, BUILTIN_REMOVE) == 0) {
        node_t inexp = child_at(1, node);
        depth_pre(__get_exp_code, child_at(2, inexp), value, NULL, NULL);
        depth_pre(__get_exp_code, child_at(0, inexp), value, NULL, NULL);
        printf("pop $%lu // val\n", *temp);
        printf("pop $%lu // set\n", *temp + 1);
        int exp_type = eval_exp_type(child_at(0, inexp));
        printf("param %d\n", exp_type);
        printf("param $%lu\n", *temp);
        printf("param $%lu\n", *temp + 1);
        printf("call remove, 3\n");
      }
      // printf("pop $%lu\n", *temp);
    }
    ret_code = 1;
  }
  if (eval_exp_type(node) == CTX_ELEM) {
    printf("pop $%lu\n", *temp);
    printf("param $%lu\n", *temp);
    printf("param $0\n");
    printf("call get_var, 2\n");
  }
  return ret_code;
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
  if (idx1 == 0) {
    idx1 = __get_par_index(varname1, data->curfun, data->context);
  }
  if (idx2 == 0) {
    idx2 = __get_par_index(varname2, data->curfun, data->context);
  }
  size_t aux;
  switch (syn->op_type) {
  case OP_ASSIGN:
    if (idx2 > 0) {
      // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp + 1,
      //        temp + 1);
      printf("param $%lu\n", temp + 1);
      printf("param $0\n");
      printf("call get_var, 2\n");
      printf("pop $%lu\n", temp + 1);
    }
    __translate_cast(child_at(2, op->parent->parent), data);
    if (idx1 > 0) {
      // printf("%s $%lu[1], $%lu\n", tac_op_string(syn->op_type), temp,
      //        temp + 1);
      printf("param $%lu\n", temp + 1);
      printf("param $%lu\n", temp);
      printf("call set_var, 2\n");
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
      // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp + 1,
      //        temp + 1);
      printf("param $%lu\n", temp + 1);
      printf("param $0\n");
      printf("call get_var, 2\n");
      printf("pop $%lu\n", temp + 1);
    }
    __translate_cast(child_at(0, child_at(2, op->parent->parent)), data);
    if (idx1 > 0) {
      // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, temp);
      printf("param $%lu\n", temp);
      printf("param $0\n");
      printf("call get_var, 2\n");
      printf("pop $%lu\n", temp);
    }
    __translate_cast(child_at(0, child_at(0, op->parent->parent)), data);
    if (eval_exp_type(child_at(0, child_at(0, op->parent->parent))) ==
        CTX_SET) {
      printf("param $%lu\n", temp);
      printf("param $%lu\n", temp + 1);
      printf("call set_cmp, 2\n");
      printf("pop $%lu\n", temp);
    } else {
      printf("%s $%lu, $%lu, $%lu\n", tac_op_string(syn->op_type), temp, temp,
             temp + 1);
    }
    if (syn->op_type == OP_BIN_NEQ) {
      printf("%s $%lu, $%lu\n", tac_op_string(OP_UNI_NEG), temp, temp);
    }
    break;
  case OP_BIN_IN:;
    node_t exp1 = child_at(0, op->parent->parent);
    int exp_type = eval_exp_type(exp1);
    printf("param %d\n", exp_type);
    printf("param $%lu\n", temp);
    printf("param $%lu\n", temp + 1);
    printf("call in, 3\n");
    printf("pop $%lu\n", temp);
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
  int is_id = 0;
  char idxpref = '$';
  size_t idx = __get_declr_index(varname, data->curfun, data->context);

  if (idx == 0) {
    idxpref = '#';
    idx = __get_par_index(varname, data->curfun, data->context);
  }
  if (idx > 0) {
    if (idxpref == '#') {
      idx--;
    }
    is_id = 1;
    // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, temp);
    printf("param %c%lu\n", idxpref, idx);
    printf("param $0\n");
    printf("call get_var, 2\n");
    printf("pop $%lu\n", temp);
  }
  switch (syn->op_type) {
  case OP_UNI_INC:
  case OP_UNI_DEC:
    printf("%s $%lu, $%lu, 1\n", tac_op_string(syn->op_type), temp, temp);
    if (is_id) {
      printf("param $%lu\n", temp);
      printf("param %c%lu\n", idxpref, idx);
      printf("call set_var, 2\n");
    }
    // printf("%s $%lu[1], $%lu\n", tac_op_string(OP_ASSIGN), idx, temp);
    break;
  // case OP_UNI_REF:
  case OP_MINUS:
    printf("minus $%lu, $%lu\n", temp, temp);
    break;
  case OP_UNI_NEG:
  case OP_UNI_BIT_NEG:
    printf("%s $%lu, $%lu\n", tac_op_string(syn->op_type), temp, temp);
    break;
  case OP_POS_INC:
  case OP_POS_DEC:
    printf("// pos\n");
    // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, idx);
    printf("param %c%lu\n", idxpref, idx);
    printf("param $0\n");
    printf("call get_var, 2\n");
    printf("pop $%lu\n", temp);
    printf("%s $%lu, $%lu, 1\n", tac_op_string(syn->op_type), temp + 1, temp);
    if (is_id) {
      printf("param $%lu\n", temp + 1);
      printf("param %c%lu\n", idxpref, idx);
      printf("call set_var, 2\n");
    }
    // printf("%s $%lu[1], $%lu\n", tac_op_string(OP_ASSIGN), idx, temp +
    // 1);
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
  if (exp->data_type != CTX_ELEM) {
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
  } else {
    int idx = 3;
    switch (exp->cast) {
    case CTX_CHAR:
      idx--;
    case CTX_INT:
      idx--;
    case CTX_FLOAT:
      idx--;
    default:
      printf("mov $%lu, $%d[%d]\n", temp + 1, 0, idx);
      break;
    }
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
  CTX_sym_t var = lookup_symbol(id, context);
  while (context != fun->context->parent) {
    if (var != NULL && (fun->params == NULL || indexOf(var, fun->params) < 0)) {
      MAP(
          if (fun->params == NULL || indexOf(MAP_val, fun->params) < 0) {
            idx++;
            if (strcmp(CTX_SYM(MAP_val)->id, id) == 0) {
              break;
            }
          },
          context->value);
    }
    context = context->parent;
  }
  return idx;
}

size_t __get_par_index(char *id, char *curfun, node_t context) {
  size_t idx = 0;
  CTX_fun_t fun = CTX_FUN(lookup_symbol(curfun, context));
  CTX_sym_t var = lookup_symbol(id, fun->context);
  if (var != NULL && fun->params != NULL && indexOf(var, fun->params) >= 0) {
    MAP(
        if (fun->params != NULL && indexOf(MAP_val, fun->params) >= 0) {
          idx++;
          if (strcmp(CTX_SYM(MAP_val)->id, id) == 0) {
            break;
          }
        },
        fun->context->value);
  }
  return idx;
}

void __get_fun_suffix(char *fun_name, node_t context, char *buffer) {
  char *data[2] = {buffer, fun_name};
  *buffer = '\0';
  depth_pre(__search_fun, context, data, NULL, NULL);
}

int __search_fun(node_t node, void *data) {
  char **datad = data;
  CTX_sym_t sym = lookup_symbol(datad[1], node);
  if (sym != NULL && strcmp(sym->id, FUN_MAIN) != 0) {
    *(*datad)++ = 'f';
    **datad = '\0';
    int idx = indexOf(sym, CTX_FUN(sym)->context->parent->value);
    sprintf(*datad, "%d", idx);
    *datad += strlen(*datad);
    node_t aux = CTX_FUN(sym)->context->parent;
    while (aux->parent != NULL) {
      idx = indexOf(aux, aux->parent->children);
      sprintf(*datad, "%d", idx);
      *datad += strlen(*datad);
      aux = aux->parent;
    }
    return 1;
  }
  return 0;
}
