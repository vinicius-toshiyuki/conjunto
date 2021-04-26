#include <context.h>
#include <ctype.h>
#include <set.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syntatic_node.h>
#include <tree.h>
#include <util.h>

SYN_value_t create_syn_val(int type, char *name) {
  void *value;
  switch (type) {
  case SYN_TAG:
    value = SYN_TAG(malloc(sizeof(struct syn_tag)));
    break;
  case SYN_EXP:
  case SYN_EXP_COMP:
    value = SYN_EXP(malloc(sizeof(struct syn_exp)));
    SYN_EXP(value)->data_type = CTX_UNK;
    SYN_EXP(value)->depth = 0;
    SYN_EXP(value)->cast = CTX_INV;
    break;
  case SYN_OP:
    value = SYN_OP(malloc(sizeof(struct syn_op)));
    SYN_OP(value)->op_type = OP_UNK;
    break;
  case SYN_TYPE:
    value = SYN_TYPE(malloc(sizeof(struct syn_type)));
    break;
  default:
    exit(EXIT_FAILURE);
  }
  SYN_VALUE(value)->name = name;
  SYN_VALUE(value)->type = type;
  return value;
}

void delete_syn_val(SYN_value_t value) {
  switch (value->type) {
  case SYN_TAG:
    break;
  case SYN_EXP_COMP:
    break;
  case SYN_EXP:
    free(SYN_EXP(value)->name);
    break;
  case SYN_OP:
    free(SYN_OP(value)->name);
    break;
  case SYN_TYPE:
    free(SYN_TYPE(value)->name);
    break;
  default:
    free(value);
    exit(EXIT_FAILURE);
  }
  free(value);
}

void init_syn_exp(int data_type, int depth, SYN_exp_t exp) {
  exp->data_type = data_type;
  exp->depth = depth;
}

void init_syn_tag(SYN_tag_t tag) {}

void init_syn_op(int op_type, SYN_op_t op) { op->op_type = op_type; }

void init_syn_type(SYN_type_t type) {}

void __recursive_free(int type, void *value, int depth, int *length) {
  /* NOTE: isso aqui tem cara de que dá errado */
  if (depth > 1) {
    for (int i = 0; i < *length++; i++) {
      __recursive_free(type, ((void **)value)[i], depth - 1, length);
      free(((void **)value)[i]);
    }
  } else {
    switch (type) {
    case CTX_INT:
    case CTX_FLOAT:
    case CTX_CHAR:
      free(value);
      break;
    case CTX_ELEM:
      delete_set_elem(value);
      break;
    case CTX_SET:
      delete_set(value);
      break;
    case CTX_UNK:
      /* Não devia ter um valor com profundidade e CTX_UNK */
      break;
    default:
      exit(EXIT_FAILURE);
    }
  }
}

void print_syn_exp(SYN_exp_t exp) {
  printf("(%s", data_type_string(exp->data_type));
  for (int i = 0; i < exp->depth; i++) {
    printf("%s*", !i ? " " : "");
  }
  printf(")");
}

void __print_syn_exp(void *value, int data_type, int depth, int *length) {
  if (depth > 1) {
    printf("[");
    for (int i = 0; i < *length; i++) {
      /* *(((int **)value)) é só para dereferenciar, pode ser qualquer ponteiro
       */
      __print_syn_exp(*(((int **)value) + i), data_type, depth - 1, length + 1);
    }
    printf("]");
  } else if (depth == 1) {
    printf("[");
    for (int i = 0; i < *length; i++) {
      __print_syn_exp(*((char **)value) + i, data_type, -1, NULL);
      if (i < *length - 1) {
        printf(", ");
      }
    }
    printf("]");
  } else {
    switch (data_type) {
    case CTX_CHAR:;
      char chr = *((char *)value);
      if (isprint(chr)) {
        printf("'%c'", chr);
      } else {
        printf("\\x%02x", chr);
      }
      break;
    case CTX_INT:
      printf("%d", *((int *)value));
      break;
    case CTX_FLOAT:
      printf("%lf", *((float *)value));
      break;
    case CTX_ELEM:;
      set_elem_t set_el = SET_ELEM(value);
      /* TODO: Não dá para ter um elemento de dado composto */
      __print_syn_exp(set_el->value, set_el->data_type, 0, NULL);
      break;
    case CTX_SET:
      printf("{");
      MAP(
          {
            __print_syn_exp(MAP_val, CTX_ELEM, 0, NULL);
            printf("%s", MAP_i < ((set_t)value)->size - 1 ? ", " : "");
          },
          value);
      printf("}");
      break;
    case CTX_UNK:
      printf("unknown");
      break;
    default:
      fprintf(stderr, "Invalid type in __print_syn_exp()\n");
      exit(EXIT_FAILURE);
    }
  }
}

const char *operator_string(int code) {
  switch (code) {
  case OP_UNK:
    return "unknown";
  case OP_ASSIGN:
    return "=";
  case OP_ASSIGN_ADD:
    return "+=";
  case OP_ASSIGN_SUB:
    return "-=";
  case OP_ASSIGN_MUL:
    return "*=";
  case OP_ASSIGN_DIV:
    return "/=";
  case OP_ASSIGN_OR:
    return "|=";
  case OP_ASSIGN_AND:
    return "&=";
  case OP_ASSIGN_XOR:
    return "^=";
  case OP_TER_FIRST:
    return "?";
  case OP_TER_LAST:
    return ":";
  case OP_BIN_OR:
    return "||";
  case OP_BIN_AND:
    return "&&";
  case OP_BIN_BIT_OR:
    return "|";
  case OP_BIN_BIT_AND:
    return "&";
  case OP_BIN_XOR:
    return "^";
  case OP_BIN_EQ:
    return "==";
  case OP_BIN_NEQ:
    return "!=";
  case OP_BIN_LT:
    return "<";
  case OP_BIN_GT:
    return ">";
  case OP_BIN_LTE:
    return "<=";
  case OP_BIN_GTE:
    return ">=";
  case OP_BIN_SHIFT_L:
    return "<<";
  case OP_BIN_SHIFT_R:
    return ">>";
  case OP_BIN_IN:
    return "in";
  case OP_PLUS:
    return "+";
  case OP_MINUS:
    return "-";
  case OP_STAR:
    return "*";
  case OP_DIV:
    return "/";
  case OP_MOD:
    return "%";
  case OP_UNI_INC:
    return "++";
  case OP_UNI_DEC:
    return "--";
  case OP_UNI_REF:
    return "&";
  case OP_UNI_NEG:
    return "!";
  case OP_UNI_BIT_NEG:
    return "~";
  case OP_POS_INC:
    return "++";
  case OP_POS_DEC:
    return "--";
  default:
    fprintf(stderr, "Invalid operator code in operator_string()\n");
    exit(EXIT_FAILURE);
  }
}
int operator_code(const char *string) {
  if (strcmp(string, "unknown") == 0) {
    return OP_UNK;
  } else if (strcmp(string, "=") == 0) {
    return OP_ASSIGN;
  } else if (strcmp(string, "+=") == 0) {
    return OP_ASSIGN_ADD;
  } else if (strcmp(string, "-=") == 0) {
    return OP_ASSIGN_SUB;
  } else if (strcmp(string, "*=") == 0) {
    return OP_ASSIGN_MUL;
  } else if (strcmp(string, "/=") == 0) {
    return OP_ASSIGN_DIV;
  } else if (strcmp(string, "|=") == 0) {
    return OP_ASSIGN_OR;
  } else if (strcmp(string, "&=") == 0) {
    return OP_ASSIGN_AND;
  } else if (strcmp(string, "^=") == 0) {
    return OP_ASSIGN_XOR;
  } else if (strcmp(string, "?") == 0) {
    return OP_TER_FIRST;
  } else if (strcmp(string, ":") == 0) {
    return OP_TER_LAST;
  } else if (strcmp(string, "||") == 0) {
    return OP_BIN_OR;
  } else if (strcmp(string, "&&") == 0) {
    return OP_BIN_AND;
  } else if (strcmp(string, "|") == 0) {
    return OP_BIN_BIT_OR;
  } else if (strcmp(string, "&") == 0) {
    return OP_BIN_BIT_AND;
  } else if (strcmp(string, "^") == 0) {
    return OP_BIN_XOR;
  } else if (strcmp(string, "==") == 0) {
    return OP_BIN_EQ;
  } else if (strcmp(string, "!=") == 0) {
    return OP_BIN_NEQ;
  } else if (strcmp(string, "<") == 0) {
    return OP_BIN_LT;
  } else if (strcmp(string, ">") == 0) {
    return OP_BIN_GT;
  } else if (strcmp(string, "<=") == 0) {
    return OP_BIN_LTE;
  } else if (strcmp(string, ">=") == 0) {
    return OP_BIN_GTE;
  } else if (strcmp(string, "<<") == 0) {
    return OP_BIN_SHIFT_L;
  } else if (strcmp(string, ">>") == 0) {
    return OP_BIN_SHIFT_R;
  } else if (strcmp(string, "in") == 0) {
    return OP_BIN_IN;
  } else if (strcmp(string, "+") == 0) {
    return OP_PLUS;
  } else if (strcmp(string, "-") == 0) {
    return OP_MINUS;
  } else if (strcmp(string, "*") == 0) {
    return OP_STAR;
  } else if (strcmp(string, "/") == 0) {
    return OP_DIV;
  } else if (strcmp(string, "%") == 0) {
    return OP_MOD;
  } else if (strcmp(string, "++") == 0) {
    return OP_UNI_INC;
  } else if (strcmp(string, "--") == 0) {
    return OP_UNI_DEC;
  } else if (strcmp(string, "&") == 0) {
    return OP_UNI_REF;
  } else if (strcmp(string, "!") == 0) {
    return OP_UNI_NEG;
  } else if (strcmp(string, "~") == 0) {
    return OP_UNI_BIT_NEG;
  } else if (strcmp(string, "++") == 0) {
    return OP_POS_INC;
  } else if (strcmp(string, "--") == 0) {
    return OP_POS_DEC;
  } else {
    fprintf(stderr, "Invalid operator string in operator_code()\n");
    exit(EXIT_FAILURE);
  }
}

void cast_to(int type, node_t node) {
  int data[2] = {0, type};
  depth_pre(__cast_to, node, data, NULL, NULL);
}

void __cast_to(node_t node, void *data) {
  int found = ((int *)data)[0];
  int type = ((int *)data)[1];
  if (!found &&
      (SYN_VALUE(node->value)->type == SYN_EXP ||
       SYN_VALUE(node->value)->type == SYN_EXP_COMP) &&
      SYN_EXP(node->value)->data_type != type) {
    SYN_EXP(node->value)->cast = type;
    found = 1;
  }
}
