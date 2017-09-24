#include <stdio.h>
#include <stdlib.h>
#include "evaluate.h"
#include "token.h"

bool evaluate(struct treenode * tree, struct symbols * table)
{
	if ( token_is_id(tree->token) ) {
		return get_symbol_value(table, tree->token->value);
	}
	else if ( token_is_not(tree->token) ) {
		return !evaluate(tree->right, table);
	}
	else if ( token_is_and(tree->token) ) {
		return evaluate(tree->left, table) && evaluate(tree->right, table);
	}
	else if ( token_is_or(tree->token) ) {
		return evaluate(tree->left, table) || evaluate(tree->right, table);
	}

	fprintf(stderr, "Error: unexpected tree node found during evaluation\n");
	exit(EXIT_FAILURE);
}
