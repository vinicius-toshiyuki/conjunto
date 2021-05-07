#include <builtin.h>
#include <context.h>
#include <stdio.h>

void get_var_code() {
  /* val get_var (var v, elem_cast) */
  printf("get_var:\n");
  printf("mov $0, *#0\n"); /* tipo */
  printf("seq $0, $0, %d\n", CTX_SET);
  printf("brnz GET_VAR_IS_SET, $0\n");
  printf("mov $0, *#0\n"); /* tipo */
  printf("seq $0, $0, %d\n", CTX_ELEM);
  printf("brnz GET_VAR_IS_ELEM, $0\n");
  printf("mov $0, *#0\n"); /* tipo */
  printf("mov $0, #0[1]\n");
  printf("jump GET_VAR_DONE\n");
  printf("GET_VAR_IS_ELEM:\n");

  printf("mov $0, #0[1]\n");
  printf("mov $1, #0[2]\n");
  // if sec_type == CHAR:
  printf("seq $2, $1, %d\n", CTX_CHAR);
  printf("brz GET_CHAR_SEC_TYPE_INT, $2\n");
  printf("mov $2, $0\n");
  printf("mov #1[0], $2\n");
  printf("chtoint $2, $2\n");
  printf("mov #1[1], $2\n");
  printf("inttofl $2, $2\n");
  printf("mov #1[2], $2\n");
  printf("jump GET_VAR_DONE\n");
  // if sec_type == INT:
  printf("GET_CHAR_SEC_TYPE_INT:\n");
  printf("seq $2, $1, %d\n", CTX_INT);
  printf("brz GET_CHAR_SEC_TYPE_FLOAT, $2\n");
  printf("mov $2, $0\n");
  printf("mov #1[1], $2\n");
  printf("inttoch $2, $2\n");
  printf("mov #1[0], $2\n");
  printf("chtofl $2, $2\n");
  printf("mov #1[2], $2\n");
  printf("jump GET_VAR_DONE\n");
  // if sec_type == FLOAT:
  printf("GET_CHAR_SEC_TYPE_FLOAT:\n");
  printf("seq $2, $1, %d\n", CTX_FLOAT);
  printf("brz GET_VAR_DONE, $2\n");
  printf("mov $2, $0\n");
  printf("mov #1[2], $2\n");
  printf("fltoint $2, $2\n");
  printf("mov #1[1], $2\n");
  printf("inttoch $2, $2\n");
  printf("mov #1[0], $2\n");
  printf("jump GET_VAR_DONE\n");

  printf("GET_VAR_IS_SET:\n");
  printf("mov $0, #0\n");
  printf("GET_VAR_DONE:\n");
  printf("return $0\n");
}

void set_var_code() {
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
}

void set_cmp_code() {
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
}

void in_code() {
  /* int in(int type, val v, set s) */
  printf("in:\n");
  printf("seq $0, #0, %d\n", CTX_ELEM);
  printf("brz IN_NOT_ELEM, $0\n");
  printf("mov $5, #1[2]\n");
  printf("mov $6, #1[1]\n");
  printf("jump IN_IS_ELEM\n");
  printf("IN_NOT_ELEM:\n");
  printf("mov $5, #0\n");
  printf("mov $6, #1\n");
  printf("IN_IS_ELEM:\n");

  printf("mov $0, #2[1]\n"); // $0 = s.len
  printf("mov $4, #2[2]\n"); // $4 = s.data
  // if type == CTX_SET:
  printf("seq $1, $5, %d\n", CTX_SET);
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
  printf("param $6\n");
  printf("call set_cmp, 2\n");
  printf("pop $3\n");
  printf("seq $3, $3, 1\n");
  printf("brz IN_ELSE_0, $3\n");
  printf("add $1, $1, 1\n");
  printf("return $1\n"); // return i + 1
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
  printf("mov $3, $4[$2]\n"); // $3 = s.data[i].type
  printf("seq $3, $3, $5\n");
  printf("brz IN_ELSE_1, $3\n");
  // if s.data[i].data == v:
  printf("add $2, $2, 1\n");
  printf("mov $3, $4[$2]\n"); // $3 = s.data[i].data
  printf("seq $3, $3, $6\n");
  printf("brz IN_ELSE_1, $3\n");
  printf("add $1, $1, 1\n");
  printf("return $1\n"); // return i + 1
  printf("IN_ELSE_1:\n");

  printf("add $1, $1, 1\n");
  printf("jump IN_FOR_1\n");
  printf("IN_FOR_END_1:\n");

  printf("IN_IS_SET:\n");
  printf("return 0\n");
}

void is_set_code() {
  /* int is_set(var v) */
  printf("is_set:\n");
  printf("mov $0, *#0\n");
  printf("seq $1, $0, %d\n", CTX_ELEM);
  printf("brz IS_SET_DONE, $1\n");
  printf("mov $0, #0[2]\n");
  printf("IS_SET_DONE:\n");
  printf("seq $0, $0, %d\n", CTX_SET);
  printf("return $0\n");
}

void write_code() {
  /* int write(val, mode) */
  size_t wrtbuffersize = 512;
  printf(BUILTIN_WRITE ":\n");
  printf("mema $0, %lu\n", wrtbuffersize);
  printf("param #0\n");
  printf("param #1\n");
  printf("param $0\n");
  printf("param %lu\n", wrtbuffersize);
  printf("param 0\n");
  printf("call " BUILTIN_WRITE "_aux, 5\n");
  printf("memf $0\n");
  printf("pop $0\n");
  printf("return $0\n");
  printf(BUILTIN_WRITE "_aux:\n");
  printf("seq $0, #1, 0\n");
  printf("brz CHECK_STRING, $0\n"); /* Não string */
  printf("print #0\n");
  printf("jump ENDWRT\n");
  printf("CHECK_STRING:\n"); /* String */
  printf("seq $0, #1, 1\n");
  printf("brz WRITE_SET, $0\n");
  printf("mov $0, 0\n"); /* $0 = index */
  printf("STARTSTR:\n");
  printf("mov $1, #0[$0]\n"); /* $1 = string[index] */
  printf("mov $2, '\\0'\n");
  printf("seq $2, $2, $1\n"); /* string[index] == '\0' */
  printf("brnz ENDWRT, $2\n");
  printf("print $1\n");      /* print string[index] */
  printf("add $0, $0, 1\n"); /* index++ */
  printf("jump STARTSTR\n");
  printf("WRITE_SET:\n"); /* Set */
  printf("print '{'\n");

  printf("seq $0, #3, #4\n");
  printf("brnz ENDSET, $1\n");

  printf("mov $0, 0\n"); /* $0 = i */
  printf("WRT_LOOKUP_SET:\n");
  printf("seq $1, $0, #4\n");
  printf("brnz WRT_LOOKUP_SET_END, $1\n");
  printf("mov $1, #2[$0]\n");
  printf("seq $1, $1, #0\n");
  printf("brz NOT_FOUND, $1\n");
  printf("print '.'\n");
  printf("print '.'\n");
  printf("print '.'\n");
  printf("jump ENDSET\n");
  printf("NOT_FOUND:\n");
  printf("add $0, $0, 1\n");
  printf("jump WRT_LOOKUP_SET\n");
  printf("WRT_LOOKUP_SET_END:\n");

  printf("mov #2[#4], #0\n"); /* push s */
  printf("add #4, #4, 1\n");

  printf("mov $0, 0\n");     /* $0 = i */
  printf("mov $1, #0[1]\n"); /* $1 = val.len */
  printf("mov $2, #0[2]\n"); /* $2 = val.data */
  printf("STARTSET:\n");
  printf("seq $3, $1, $0\n");
  printf("brnz ENDSET, $3\n");
  printf("mul $3, $0, 2\n");  /* $3 = i * 2 */
  printf("mov $4, $2[$3]\n"); /* $4 = val.data[i].type */
  printf("seq $4, $4, %d\n", CTX_SET);
  printf("brz WRT_MODE_ASSIGNED, $4\n");
  printf("mov $4, 2\n"); /* print_mode = 2 */
  printf("WRT_MODE_ASSIGNED:\n");
  printf("add $3, $3, 1\n");  /* $3 = i * 2 + 1 */
  printf("mov $5, $2[$3]\n"); /* $5 = val.data[i].data */
  printf("param $5\n");
  printf("param $4\n");
  printf("param #2\n");
  printf("param #3\n");
  printf("param #4\n");
  printf("call " BUILTIN_WRITE "_aux, 5\n");
  printf("pop $3\n");        /* Descarta valor */
  printf("sub $3, $1, 1\n"); /* $3 = val.len - 1 */
  printf("seq $3, $3, $0\n");
  printf("brnz WRT_LAST, $3\n");
  printf("print ','\n");
  printf("print ' '\n");
  printf("WRT_LAST:\n");
  printf("add $0, $0, 1\n"); /* i++ */
  printf("jump STARTSET\n");
  printf("ENDSET:\n");
  printf("print '}'\n");
  printf("ENDWRT:\n");
  printf("return 0\n");
}

void writeln_code() {
  /* int writeln(val) */
  printf(BUILTIN_WRITELN ":\n");
  printf("param #0\n");
  printf("param #1\n");
  printf("call " BUILTIN_WRITE ", 2\n");
  printf("println\n");
  printf("return 0\n");
}

void read_code() {
  /* int read(var) */
  printf(BUILTIN_READ ":\n");
  printf("mov $0, *#0\n"); /* $0 = data type */
  // if var.type == elem
  printf("seq $1, $0, %d\n", CTX_ELEM);
  printf("brz READ_NOT_ELEM, $1\n");
  printf("mov $0, #0[2]\n"); // $0 = var.sec_type
  printf("READ_NOT_ELEM:\n");
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
}

void add_code() {
  /* set add(type, val, tgt) */
  printf("set_" BUILTIN_ADD ":\n");
  printf("seq $0, #0, %d\n", CTX_ELEM);
  printf("brz ADD_NOT_ELEM, $0\n");
  printf("mov $6, #1[2]\n");
  printf("mov $7, #1[1]\n");
  printf("jump ADD_IS_ELEM\n");
  printf("ADD_NOT_ELEM:\n");
  printf("mov $6, #0\n");
  printf("mov $7, #1\n");
  printf("ADD_IS_ELEM:\n");
  // if val in tgt:
  printf("param $6\n");
  printf("param $7\n");
  printf("param #2\n");
  printf("call in, 3\n");
  printf("pop $0\n");
  printf("slt $0, 0, $0\n");
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
  printf("mov $0[$4], $6\n"); // data[i * 2] = type
  printf("add $4, $4, 1\n");
  printf("mov $0[$4], $7\n"); // data[i * 2 + 1] = val
  printf("mov $1, #2[2]\n");
  printf("memf $1\n");       // free tgt.data
  printf("mov #2[2], $0\n"); // tgt.data = data
  printf("mov $0, #2[1]\n");
  printf("add $0, $0, 1\n");
  printf("mov #2[1], $0\n"); // tgt.len++
  printf("ADD_END:\n");
  printf("return #2\n");
}

void exists_code() {
  /* int exists(var v, set s) */
  /* NOTE: recebe a variável, não seu valor */
  printf("exists:\n");
  printf("mov $0, #1[1]\n"); // $0 = s.len
  printf("mov $1, #1[2]\n"); // $1 = s.data
  printf("mov $2, *#0\n");   // v.type
  // for  i in 0..$0:
  printf("mov $3, 0\n"); // $1 = i
  printf("EXISTS_FOR:\n");
  printf("seq $4, $3, $0\n");
  printf("brnz EXISTS_FOR_END, $4\n");
  printf("mul $4, $3, 2\n");  // $4 = i * 2
  printf("mov $5, $1[$4]\n"); // $5 = s.data[i].type
  printf("seq $5, $4, $2\n");
  printf("brz EXISTS_DIFF_TYPE, $5\n");
  /* TODO: sempre o primeiro valor */
  printf("EXISTS_IS_ELEM:\n");
  printf("add $4, $4, 1\n");  // $4 += 1
  printf("mov $5, $1[$4]\n"); // $5 = s.data[i].data
  printf("mov #0[1], $5\n");  // v.data = $5
  printf("jump EXISTS_FOR_END\n");
  printf("EXISTS_DIFF_TYPE:\n");
  // if v.type == CTX_ELEM:
  printf("seq $5, $2, %d\n", CTX_ELEM);
  printf("brz EXISTS_NOT_ELEM, $5\n");
  printf("mov $5, $1[$4]\n"); // $5 = s.data[i].type
  printf("mov #0[2], $5\n");  // v.sec_type = $5
  printf("jump EXISTS_IS_ELEM\n");
  printf("EXISTS_NOT_ELEM:\n");
  printf("add $3, $3, 1\n"); // i++
  printf("jump EXISTS_FOR\n");
  printf("EXISTS_FOR_END:\n");
  // printf("mov $0, #0[1]\n");
  printf("return #0\n"); /* TODO: tem que retornar a variável? */
}

void remove_code() {
  /* int remove(type t, val v, set s) */
  printf(BUILTIN_REMOVE ":\n");
  printf("seq $0, #0, %d\n", CTX_ELEM);
  printf("brz REMOVE_NOT_ELEM, $0\n");
  printf("mov $0, #1[2]\n");
  printf("mov $1, #1[1]\n");
  printf("jump REMOVE_IS_ELEM\n");
  printf("REMOVE_NOT_ELEM:\n");
  printf("mov $0, #0\n");
  printf("mov $1, #1\n");
  printf("REMOVE_IS_ELEM:\n");
  // if v in s:
  printf("param $0\n");
  printf("param $1\n");
  printf("param #2\n");
  printf("call in, 3\n");
  printf("pop $0\n"); /* $0 é o índice do elemento */
  printf("seq $1, $0, 0\n");
  printf("brnz REMOVE_END, $1\n");

  printf("sub $0, $0, 1\n");

  printf("mov $1, 0\n");     /* $1 = i */
  printf("mov $2, #2[1]\n"); /* $2 = s.len */
  printf("sub $3, $2, 1\n");
  printf("mul $3, $3, 2\n"); /* novo len */
  printf("mov $4, $3\n");    /* idx = 0 */
  printf("mema $3, $4\n");
  printf("mov $4, 0\n"); /* idx = 0 */

  /* for i in 0..$2 */
  printf("REMOVE_FOR:\n");
  printf("seq $5, $2, $1\n");
  printf("brnz REMOVE_FOR_END, $5\n");

  /* if idx == i */
  printf("seq $5, $0, $1\n");
  printf("brnz REMOVE_IGNORE_IDX, $5\n");
  printf("mul $5, $4, 2\n");  /* $5 = idx * 2 */
  printf("mul $6, $1, 2\n");  /* $6 = i * 2 */
  printf("mov $7, #2[2]\n");  /* $7 = s.data */
  printf("mov $8, $7[$6]\n"); /* $8 = s.data[i].type */
  printf("mov $3[$5], $8\n"); /* new[idx].type = $8 */
  printf("add $5, $5, 1\n");
  printf("add $6, $6, 1\n");
  printf("mov $8, $7[$6]\n"); /* $8 = s.data[i].data */
  printf("mov $3[$5], $8\n"); /* new[idx].data = $8 */
  printf("add $4, $4, 1\n");
  printf("REMOVE_IGNORE_IDX:\n");

  printf("add $1, $1, 1\n");
  printf("jump REMOVE_FOR\n");
  printf("REMOVE_FOR_END:\n");

  printf("mov $0, #2[2]\n");
  printf("memf $0\n");
  printf("mov #2[2], $3\n"); /* s.data = new */
  printf("mov $0, #2[1]\n");
  printf("sub $0, $0, 1\n");
  printf("mov #2[1], $0\n"); /* s.len-- */
  printf("REMOVE_END:\n");

  printf("return #2\n");
}
