#include <context.h>
#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTX_sym_t create_symbol(int type, char *id, int data_type, int lnum, int lcol) {
  void *sym = NULL;
  switch (type) {
  case CTX_VAR:
    sym = malloc(sizeof(struct ctx_variable));
    CTX_VAR(sym)->secondary_data_type = CTX_UNK;
    CTX_VAR(sym)->value = NULL;
    CTX_VAR(sym)->depth = 0;
    CTX_VAR(sym)->length = NULL;
    break;
  case CTX_FUN:
    sym = malloc(sizeof(struct ctx_function));
    CTX_FUN(sym)->params = NULL;
    CTX_FUN(sym)->context = NULL;
    break;
  }
  CTX_SYM(sym)->type = type;
  CTX_SYM(sym)->id = id;
  CTX_SYM(sym)->data_type = data_type;
  CTX_SYM(sym)->lnum = lnum;
  CTX_SYM(sym)->lcol = lcol;
  return sym;
}

void delete_symbol(CTX_sym_t sym) {
  switch (sym->type) {
  case CTX_VAR:
    if (CTX_VAR(sym)->value != NULL) {
      free(CTX_VAR(sym)->value);
    }
    if (CTX_VAR(sym)->length != NULL) {
      free(CTX_VAR(sym)->length);
    }
    break;
  case CTX_FUN:
    if (CTX_FUN(sym)->params != NULL) {
      delete_list(CTX_FUN(sym)->params);
    }
    break;
  }
  free(sym);
}

void init_ctx_var(void *value, int depth, int *length, CTX_var_t var) {
  var->value = value;
  var->depth = depth;
  var->length = length;
}

void init_ctx_fun(list_t params, CTX_fun_t fun) { fun->params = params; }

CTX_sym_t lookup_symbol(char *id, node_t ctx) {
  CTX_sym_t sym = NULL;
  while (sym == NULL && ctx != NULL) {
    MAP(
        if (strcmp(CTX_SYM(MAP_val)->id, id) == 0) {
          sym = MAP_val;
          break;
        },
        ctx->value);
    ctx = ctx->parent;
  }
  return sym;
}

int has_symbol(char *id, list_t local_ctx) {
  for (elem_t it = local_ctx->first; it != NULL; it = it->next) {
    if (strcmp(CTX_SYM(it->value)->id, id) == 0) {
      return 0;
    }
  }
  return -1;
}

const char *type_string(int type) {
  switch (type) {
  case CTX_FUN:
    return "function";
  case CTX_VAR:
    return "variable";
  default:
    fprintf(stderr, "Invalid type code in type_string(): %d\n", type);
    exit(EXIT_FAILURE);
  }
}

const char *data_type_string(int type) {
  switch (type) {
  case CTX_INT:
    return "int";
  case CTX_FLOAT:
    return "float";
  case CTX_CHAR:
    return "char";
  case CTX_ELEM:
    return "elem";
  case CTX_SET:
    return "set";
  case CTX_INEXP:
    return "in-expression";
  case CTX_UNK:
    return "unknown";
  case CTX_INV:
    return "invalid";
  default:
    fprintf(stderr, "Invalid type code in data_type_string(): %d\n", type);
    exit(EXIT_FAILURE);
  }
}

const int type_code(const char *type) {
  if (strcmp(type, "variable") == 0) {
    return CTX_VAR;
  } else if (strcmp(type, "function") == 0) {
    return CTX_FUN;
  } else {
    fprintf(stderr, "Invalid type string in type_code(): %s\n", type);
    exit(EXIT_FAILURE);
  }
}

const int data_type_code(const char *type) {
  if (strcmp(type, "int") == 0) {
    return CTX_INT;
  } else if (strcmp(type, "float") == 0) {
    return CTX_FLOAT;
  } else if (strcmp(type, "char") == 0) {
    return CTX_CHAR;
  } else if (strcmp(type, "elem") == 0) {
    return CTX_ELEM;
  } else if (strcmp(type, "set") == 0) {
    return CTX_SET;
  } else if (strcmp(type, "in-expression") == 0) {
    return CTX_INEXP;
  } else if (strcmp(type, "unknown") == 0) {
    return CTX_UNK;
  } else if (strcmp(type, "invalid") == 0) {
    return CTX_INV;
  } else {
    fprintf(stderr, "Invalid type string in data_type_code(): %s\n", type);
    exit(EXIT_FAILURE);
  }
}

int compare_symbol(void *a, void *b) {
  return strcmp(CTX_SYM(a)->id, CTX_SYM(b)->id);
}
