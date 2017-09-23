#ifndef SATISFIABILITY_PARSER_H
#define SATISFIABILITY_PARSER_H

#include "token.h"
#include "treenode.h"

struct treenode * get_expr(struct token * in, struct token ** out);
struct treenode * get_term(struct token * in, struct token ** out);
struct treenode * get_element(struct token * in, struct token ** out);
struct treenode * get_factor(struct token * in, struct token ** out);

#endif  /*  SATISFIABILITY_PARSER_H  */
