#ifndef SATISFIABILITY_PARSER_H
#define SATISFIABILITY_PARSER_H

#include "token.h"
#include "treenode.h"
#include "symbols.h"

struct treenode * get_expr(struct token * in, struct token ** out, struct symbols * table);
struct treenode * get_term(struct token * in, struct token ** out, struct symbols * table);
struct treenode * get_elem(struct token * in, struct token ** out, struct symbols * table);
struct treenode * get_fact(struct token * in, struct token ** out, struct symbols * table);

#endif  /*  SATISFIABILITY_PARSER_H  */
