#ifndef __EVAL_H__
#define __EVAL_H__

#include <syntatic_node.h>
#include <tree.h>

int eval_exp_type(node_t exp);

int eval_max_type(int type1, int type2);

int can_cast(int type1, int type2);

#endif
