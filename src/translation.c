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
  /* Preencher .table com context */
  /* Definir funções de tree */
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
  /***********************/
  /* val get_var (var v) */
  printf("get_var:\n");
  printf("mov $0, *#0\n"); /* tipo */
  printf("seq $0, $0, %d\n", CTX_SET);
  printf("brnz GET_VAR_IS_SET, $0\n");
  printf("mov $0, #0[1]\n");
  printf("jump GET_VAR_NOT_SET\n");
  printf("GET_VAR_IS_SET:\n");
  printf("mov $0, #0\n");
  printf("GET_VAR_NOT_SET:\n");
  printf("return $0\n");
  /***********************/
  /* void set_var (val v, var r) */
  printf("set_var:\n");
  printf("mov $0, *#1\n"); /* tipo */
  printf("seq $0, $0, %d\n", CTX_SET);
  printf("brnz SET_VAR_IS_SET, $0\n");
  printf("mov #1[1], #0\n");
  printf("jump SET_VAR_END\n");
  printf("SET_VAR_IS_SET:\n");
  // if v == empty:
  printf("mov $0, &empty\n");
  printf("seq $0, $0, #0\n");
  printf("brz SET_VAR_END, $0\n");
  // r[1] = 0
  printf("mov #1[1], 0\n");
  printf("SET_VAR_END:\n");
  printf("return\n");
  /***********************/
  /* int set_cmp(set s1, set s2) */
  printf("set_cmp:\n");
  // if s1.len != s2.len:
  //   return 0
  printf("mov $0, #0[1]\n");
  printf("mov $1, #1[1]\n");
  printf("seq $0, $0, $1\n");
  printf("brnz SET_LEN_EQ, $0\n");
  printf("return 0\n");
  printf("SET_LEN_EQ:\n");
  printf("mov $7, #0[2]\n"); // $7 = s1.data
  printf("mov $8, #1[2]\n"); // $8 = s2.data
  // for i in 0..s1.len:
  printf("mov $0, 0\n"); // $0 = i
  printf("SET_FOR:\n");
  printf("seq $2, $0, $1\n");
  printf("brnz SET_FOR_END, $2\n");
  // for j in 0..s1.len:
  printf("mov $2, 0\n"); // $2 = j
  printf("SET_FOR_2:\n");
  printf("seq $3, $2, $1\n");
  printf("brnz DIFFERENT, $3\n");
  // if s1[i][0] == s2[j][0]:
  printf("mul $3, $0, 2\n"); // $3 = i * 2
  printf("mov $5, $7[$3]\n");
  printf("mul $4, $2, 2\n"); // $4 = j * 2
  printf("mov $6, $8[$4]\n");
  printf("seq $5, $5, $6\n");
  printf("brz NOT_SAME_TYPE, $5\n");
  // if s1[i][0] == 0
  printf("seq $5, $6, %d\n", CTX_SET);
  printf("add $3, $3, 1\n");
  printf("add $4, $4, 1\n");
  printf("mov $3, $7[$3]\n"); // $3 = s1.data[i][1]
  printf("mov $4, $8[$4]\n"); // $4 = s2.data[i][1]
  printf("brnz IF_SET_TYPE, $5\n");
  // if s1[i][1] == s2[j][1]
  printf("seq $3, $3, $4\n");
  printf("brnz FOUND, $3\n");
  printf("jump NOT_SAME_TYPE\n");
  printf("IF_SET_TYPE:\n");
  // if cmp s1[i][1], s2[j][1]
  printf("param $3\n");
  printf("param $4\n");
  printf("call set_cmp, 2\n");
  printf("pop $3\n");
  printf("brnz FOUND, $3\n");
  printf("NOT_SAME_TYPE:\n");
  printf("add $2, $2, 1\n"); // j++
  printf("jump SET_FOR_2\n");
  printf("DIFFERENT:\n");
  printf("return 0\n");
  printf("SET_FOR_END_2:\n");
  printf("FOUND:\n");
  printf("add $0, $0, 1\n"); // i++
  printf("jump SET_FOR\n");
  printf("SET_FOR_END:\n");
  printf("return 1\n");
  /*************************************/
  /* int in(int type, val v, set s) */
  printf("in:\n");
  printf("mov $0, #2[1]\n"); // $0 = s.len
  printf("mov $4, #2[2]\n"); // $4 = s.data
  // if type == CTX_SET:
  printf("seq $1, #0, %d\n", CTX_SET);
  printf("brz IN_NOT_SET, $1\n");

  // for i in 0..s.len:
  printf("mov $1, 0\n"); // $1 = i
  printf("IN_FOR_0:\n");
  printf("seq $2, $1, $0\n");
  printf("brnz IN_FOR_END_0, $2\n");
  // if s.data[i][0] == CTX_SET:
  printf("mul $2, $1, 2\n");  // $2 = i * 2
  printf("mov $3, $4[$2]\n"); // $3 = s.data[0][0]
  printf("seq $3, $3, %d\n", CTX_SET);
  printf("brz IN_ELSE_0, $3\n");
  // if set_cmp s.data[i][1], v:
  printf("add $2, $2, 1\n");
  printf("mov $3, $4[$2]\n"); // $3 = s.data[0][1]
  printf("param $3\n");
  printf("param #1\n");
  printf("call set_cmp, 2\n");
  printf("pop $3\n");
  printf("seq $3, $3, 1\n");
  printf("brz IN_ELSE_0, $3\n");
  printf("return 1\n");
  printf("IN_ELSE_0:\n");

  printf("add $1, $1, 1\n");
  printf("jump IN_FOR_0\n");
  printf("IN_FOR_END_0:\n");
  printf("jump IN_IS_SET\n");

  printf("IN_NOT_SET:\n");
  // for i in 0..s.len:
  printf("mov $1, 0\n"); // $1 = i
  printf("IN_FOR_1:\n");
  printf("seq $2, $1, $0\n");
  printf("brnz IN_FOR_END_1, $2\n");
  // if s.data[i][0] != CTX_SET:
  printf("mul $2, $1, 2\n");  // $2 = i * 2
  printf("mov $3, $4[$2]\n"); // $3 = s.data[0][0]
  printf("seq $3, $3, #0\n");
  printf("brz IN_ELSE_1, $3\n");
  // if set_cmp s.data[i][1], v:
  printf("add $2, $2, 1\n");
  printf("mov $3, $4[$2]\n"); // $3 = s.data[0][1]
  printf("seq $3, $3, #1\n");
  printf("brz IN_ELSE_1, $3\n");
  printf("return 1\n");
  printf("IN_ELSE_1:\n");

  printf("add $1, $1, 1\n");
  printf("jump IN_FOR_1\n");
  printf("IN_FOR_END_1:\n");

  printf("IN_IS_SET:\n");
  printf("return 0\n");
  /****************************/
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
  /****************************/
  /* int writeln(val) */
  printf(BUILTIN_WRITELN ":\n");
  printf("param #0\n");
  printf("param #1\n");
  printf("call " BUILTIN_WRITE ", 2\n");
  printf("println\n");
  printf("return 0\n");
  /****************************/
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
  /**************************************/
  /* int is_set(set) */
  // printf(BUILTIN_ISSET ":\n");
  printf("mov $0, *#0\n");
  printf("seq $0, $0, %d\n", CTX_SET);
  printf("return $0\n");
  /**************************************/
  /* set add(type, val, tgt) */
  printf("set_" BUILTIN_ADD ":\n");
  printf("mov $0, #0\n"); /* data type */
  // if val in tgt:
  printf("param #0\n");
  printf("param #1\n");
  printf("param #2\n");
  printf("call in, 3\n");
  printf("pop $0\n");
  printf("seq $0, $0, 1\n");
  printf("brz ADD_NOT_IN, $0\n");
  printf("jump ADD_END\n");
  // else:
  printf("ADD_NOT_IN:\n");
  printf("mov $0, #2[1]\n"); // $0 = tgt.len
  printf("add $0, $0, 1\n"); // $0 += 1
  printf("mul $0, $0, 2\n"); // $0 *= 2
  printf("mema $1, $0\n");
  printf("mov $0, $1\n");    // $0 = data[]
  printf("mov $1, #2[2]\n"); // $1 = tgt.data
  // for i in 0..$2
  printf("mov $2, #2[1]\n"); // $2 = tgt.len
  printf("mov $3, 0\n");     // i = 0
  printf("ADD_FOR:\n");
  printf("seq $4, $3, $2\n");
  printf("brnz ADD_FOR_END, $4\n");
  printf("mul $4, $3, 2\n"); // $4 = i * 2
  printf("mov $5, $1[$4]\n");
  printf("mov $0[$4], $5\n"); // data[i * 2] = tgt.data[i * 2]
  printf("add $4, $4, 1\n");  // $4 += 1
  printf("mov $5, $1[$4]\n");
  printf("mov $0[$4], $5\n"); // data[i * 2 + 1] = tgt.data[i * 2 + 1]
  printf("add $3, $3, 1\n");  // i++
  printf("jump ADD_FOR\n");
  printf("ADD_FOR_END:\n");
  printf("mul $4, $3, 2\n");  // $4 = i * 2
  printf("mov $0[$4], #0\n"); // data[i * 2] = type
  printf("add $4, $4, 1\n");
  printf("mov $0[$4], #1\n"); // data[i * 2 + 1] = val
  printf("mov $1, #2[2]\n");
  printf("memf $1\n");       // free tgt.data
  printf("mov #2[2], $0\n"); // tgt.data = data
  printf("mov $0, #2[1]\n");
  printf("add $0, $0, 1\n");
  printf("mov #2[1], $0\n"); // tgt.len++
  printf("ADD_END:\n");
  printf("return #2\n");
  /**************************************/
}

int __create_code(node_t node, void *value) {
  static size_t ifcount = 0, loopcount = 0;
  t9n_data_t *data = value;
  int ret_code = 0;
  SYN_value_t syn = node->value;
  // if (node->parent != NULL)
  //   printf("%s %lu\n", syn->name, node->children->size);
  size_t *temp = data->temps->last->value;
  switch (syn->type) {
  case SYN_TAG:
    if (strcmp(syn->name, TOK_DECLR_FN) == 0) {
      // add_child(
      //     create_node(create_t9n(
      //         T9N_DECLR_FN, strdup(SYN_VALUE(node->children->first)->name))),
      //     t9n_tree);
      data->curfun = SYN_VALUE(child_at(0, child_at(1, node))->value)->name;
      /* TODO:feio */
      ((t9n_data_t *)value)->curfun = data->curfun;
      CTX_fun_t fun = CTX_FUN(lookup_symbol(data->curfun, data->context));
      data->context = fun->context;
      append(calloc(1, sizeof(size_t)), data->temps);
      char suffix[512];
      __get_fun_suffix(data->curfun, data->context, suffix);
      printf("%s%s:\n", data->curfun, suffix);
      depth_pre(__create_code, node->children->last->value, value, NULL, NULL);
      printf("return 0\n");
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_DECLR) == 0) {
      MAP(
          if (MAP_i > 0) {
            char *varname = SYN_VALUE(child_at(0, MAP_val)->value)->name;
            size_t idx =
                __get_declr_index(varname, data->curfun, data->context);
            if (idx > 0) {
              char *type =
                  SYN_VALUE(child_at(0, child_at(0, node))->value)->name;
              printf("// %s %s\n", type, varname);
              printf("mema $%lu, %d\n", *temp,
                     data_type_code(type) == CTX_SET ? 3 : 2);
              printf("mov *$%lu, %d\n", (*temp)++, data_type_code(type));
              if (data_type_code(type) == CTX_SET) {
                printf("mema $%lu, 0\n", *temp);
                printf("mov $%lu[2], $%lu\n", *temp - 1, *temp);
              }
            }
          },
          node->children);
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_RETURN) == 0) {
      printf("// return exp\n");

      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);

      if (strcmp(data->curfun, FUN_MAIN) == 0) {
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
      append(temploop, data->loops);
      printf("LOOP_%lu:\n", *temploop);
      depth_pos(__get_exp_code, child_at(0, node), value, NULL, NULL);
      printf("pop $%lu\n", *temp);
      printf("brz LOOP_END_%lu, $%lu\n", *temploop, *temp);
      depth_pre(__create_code, child_at(1, node), value, NULL, NULL);
      printf("jump LOOP_%lu\n", *temploop);
      printf("LOOP_END_%lu:\n", *temploop);
      free(removeAt(data->loops->size - 1, data->loops));
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_FOR) == 0) {
      size_t *temploop = (size_t *)malloc(sizeof(size_t));
      *temploop = loopcount++;
      append(temploop, data->loops);
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
      free(removeAt(data->loops->size - 1, data->loops));
      ret_code = 1;
    } else if (strcmp(syn->name, TOK_BREAK) == 0) {
      printf("jump LOOP_END_%lu\n", *((size_t *)data->loops->last->value));
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
            size_t idx =
                __get_declr_index(varname, data->curfun, data->context);
            if (idx > 0) {
              printf("param $%lu\n", idx - 1);
              printf("call get_var, 1\n");
              printf("pop $%lu\n", *temp);
              // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), *temp,
              //        idx - 1); /* Obtém o valor da variável */
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
        size_t idx = __get_declr_index(varname, data->curfun, data->context);
        printf("param $%lu\n", idx - 1);
        printf("call read, 1\n");
      } else if (strcmp(fun_name, BUILTIN_ISSET) == 0) {
        int exp_type = eval_exp_type(child_at(1, node));
        printf("// is_set(%s)\n", data_type_string(exp_type));
        printf("push %d\n", exp_type == CTX_SET ? 1 : 0);
      } else if (strcmp(fun_name, BUILTIN_ADD) == 0) {
        node_t exp = child_at(1, node);
        int exp_type = eval_exp_type(child_at(0, exp));
        depth_pos(__get_exp_code, child_at(2, exp), value, NULL, NULL);
        depth_pos(__get_exp_code, child_at(0, exp), value, NULL, NULL);
        printf("pop $%lu // val\n", *temp);
        printf("pop $%lu // set\n", *temp + 1);

        printf("param %d // type\n", exp_type);
        printf("param $%lu\n", *temp);
        printf("param $%lu\n", *temp + 1);
        printf("call set_" BUILTIN_ADD ", 3\n");
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
    case 3:
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
      if (SYN_OP(op->value)->op_type == OP_ASSIGN &&
          strcmp(SYN_VALUE(child_at(0, node)->value)->name, TOK_ID) == 0 &&
          strcmp(SYN_VALUE(child_at(2, node)->value)->name, TOK_EMPTY) != 0 &&
          lookup_symbol(SYN_VALUE(child_at(0, child_at(0, node))->value)->name,
                        data.context)
                  ->data_type == CTX_SET) {
        char *varname = SYN_VALUE(child_at(0, child_at(0, node))->value)->name;
        size_t idx = __get_declr_index(varname, data.curfun, data.context);
        printf("mov $%lu, $%lu\n", idx - 1, *temp);
      }
      printf("push $%lu\n\n", *temp);
      /* Ver o operador */
      break;
    case 5:
    default:
      break;
    }
  }
  if (strcmp(SYN_VALUE(node->parent->value)->name, TOK_FN) == 0 &&
      child_at(node->parent->children->size - 1, node->parent) == node) {
    char *varname =
        SYN_VALUE(child_at(0, child_at(0, node->parent))->value)->name;
    size_t argcount = node->parent->children->size;
    if (!IS_BUILTIN(
            SYN_VALUE(child_at(0, child_at(0, node->parent))->value)->name)) {
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
      char suffix[512];
      __get_fun_suffix(varname, data.context, suffix);
      printf("call %s%s", varname, suffix);
      if (argcount > 1) {
        printf(", %lu", argcount - 1);
      }
      printf("\n");
    } else if (strcmp(varname, BUILTIN_ISSET) == 0) {
      MAP(
          if (MAP_i > 0) { printf("pop $%lu // discard value\n", *temp); },
          node->parent->children);
      __create_code(node->parent, value);
    } else if (strcmp(varname, BUILTIN_ADD) == 0) {
      MAP(
          if (MAP_i > 0) { printf("pop $%lu // discard value\n", *temp); },
          node->parent->children);
      __create_code(node->parent, value);
    }
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
      // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp + 1,
      //        temp + 1);
      printf("param $%lu\n", temp + 1);
      printf("call get_var, 1\n");
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
      printf("call get_var, 1\n");
      printf("pop $%lu\n", temp + 1);
    }
    __translate_cast(child_at(0, child_at(2, op->parent->parent)), data);
    if (idx1 > 0) {
      // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, temp);
      printf("param $%lu\n", temp);
      printf("call get_var, 1\n");
      printf("pop $%lu\n", temp);
    }
    __translate_cast(child_at(0, child_at(0, op->parent->parent)), data);
    printf("%s $%lu, $%lu, $%lu\n", tac_op_string(syn->op_type), temp, temp,
           temp + 1);
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
  size_t idx = __get_declr_index(varname, data->curfun, data->context);
  if (idx > 0) {
    // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, temp);
    printf("param $%lu\n", temp);
    printf("call get_var, 1\n");
    printf("pop $%lu\n", temp);
  }
  switch (syn->op_type) {
  case OP_UNI_INC:
  case OP_UNI_DEC:
    printf("%s $%lu, $%lu, 1\n", tac_op_string(syn->op_type), temp, temp);
    printf("param $%lu\n", temp);
    printf("param $%lu\n", idx - 1);
    printf("call set_var, 2\n");
    // printf("%s $%lu[1], $%lu\n", tac_op_string(OP_ASSIGN), idx - 1, temp);
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
    // printf("%s $%lu, $%lu[1]\n", tac_op_string(OP_ASSIGN), temp, idx - 1);
    printf("param $%lu\n", idx - 1);
    printf("call get_var, 1\n");
    printf("pop $%lu\n", temp);
    printf("%s $%lu, $%lu, 1\n", tac_op_string(syn->op_type), temp + 1, temp);
    printf("param $%lu\n", temp + 1);
    printf("param $%lu\n", idx - 1);
    printf("call set_var, 2\n");
    // printf("%s $%lu[1], $%lu\n", tac_op_string(OP_ASSIGN), idx - 1, temp +
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
    int idx = indexOf(sym, node->value);
    sprintf(*datad, "%d", idx);
    while (node->parent != NULL) {
      idx = indexOf(node, node->parent->children);
      sprintf(*datad, "%d", idx);
      node = node->parent;
    }
    return 1;
  }
  return 0;
}
