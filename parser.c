#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "token.h"
#include "treenode.h"

struct treenode * get_factor(struct token * in, struct token ** out)
{
	struct token * next = in;
	struct treenode * node = NULL;

	if ( token_is_id(in) ) {
		node = treenode_create(in, NULL, NULL);
		next = in->next;
	}
	else if ( token_is_lparen(in) ) {
		node = get_expr(in->next, &next);
		if ( next && token_is_rparen(next) ) {
			next = next->next;
		}
		else {
			tree_destroy(node);
			node = NULL;
			fprintf(stderr, "Error: missing closing parenthesis.\n");
		}
	}
	else {
		fprintf(stderr, "Error: missing factor\n");
	}

	*out = next;
	return node;
}

struct treenode * get_element(struct token * in, struct token ** out)
{
	struct token * next = in;
	struct treenode * node = NULL;
	struct treenode * second = NULL;

	if ( token_is_not(in) ) {
		second = get_factor(in->next, &next);
		if ( second ) {
			node = treenode_create(in, NULL, second);
			next = in->next->next;
		}
	}
	else {
		node = get_factor(in, &next);
	}

    *out = next;
	return node;
}

struct treenode * get_term(struct token * in, struct token ** out)
{
	struct token * next = in;
	struct treenode * node = NULL;
	struct treenode * second = NULL;

	if ( (node = get_element(in, &next)) ) {
		while ( token_is_and(next) ) {
			struct token * op_node = next;

			if ( (second = get_element(next->next, &next)) ) {
				node = treenode_create(op_node, node, second);
			}
			else {
				tree_destroy(node);
				node = NULL;
			}
		}
	}

    *out = next;
	return node;
}

struct treenode * get_expr(struct token * in, struct token ** out)
{
	struct token * next = in;
	struct treenode * node = NULL;
	struct treenode * second = NULL;

	if ( (node = get_term(in, &next)) != NULL ) {
		while ( token_is_or(next) ) {
			struct token * op_node = next;

			if ( (second = get_term(next->next, &next)) != NULL ) {
				node = treenode_create(op_node, node, second);
			}
			else {
				tree_destroy(node);
				node = NULL;
			}
		}
	}

    *out = next;
	return node;
}
