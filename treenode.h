#ifndef SATISFIABILITY_TREENODE_H
#define SATISFIABILITY_TREENODE_H

#include <stdbool.h>
#include "lexer.h"

struct treenode {
	bool result;
	struct token * token;
	struct treenode * left;
	struct treenode * right;
};

struct treenode * treenode_create(struct token * token,
								  struct treenode * left,
								  struct treenode * right);
void tree_destroy(struct treenode * node);
void tree_print(struct treenode * node);

#endif  /*  SATISFIABILITY_TREENODE_H  */
