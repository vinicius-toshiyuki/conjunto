#ifndef __BUILTIN_H__
#define __BUILTIN_H__

void get_var_code();
void set_var_code();
void set_cmp_code();
void in_code();
void is_set_code();
void write_code();
void writeln_code();
void read_code();
void add_code();
void exists_code();
void remove_code();

/* Built-ins */
#define BUILTIN_WRITE "write"
#define BUILTIN_WRITELN "writeln"
#define BUILTIN_READ "read"
#define BUILTIN_ISSET "is_set"
#define BUILTIN_ADD "add"
#define BUILTIN_REMOVE "remove"
#define BUILTIN_EXISTS "exists"

#define IS_BUILTIN(fun_name)                                                   \
  (strcmp(fun_name, BUILTIN_WRITE) == 0 ||                                     \
   strcmp(fun_name, BUILTIN_WRITELN) == 0 ||                                   \
   strcmp(fun_name, BUILTIN_READ) == 0 ||                                      \
   strcmp(fun_name, BUILTIN_ISSET) == 0 ||                                     \
   strcmp(fun_name, BUILTIN_ADD) == 0 ||                                       \
   strcmp(fun_name, BUILTIN_REMOVE) == 0 ||                                    \
   strcmp(fun_name, BUILTIN_EXISTS) == 0)

#endif
