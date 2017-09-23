#include <stdio.h>
#include <stdlib.h>
#include "treenode.h"

struct treenode * treenode_create(struct token * token,
								  struct treenode * left,
								  struct treenode * right)
{
	struct treenode * new_node = malloc(sizeof *new_node);
	if ( new_node == NULL ) {
		perror("couldn't allocate memory for treenode");
		exit(EXIT_FAILURE);
	}

	new_node->token = copy_token(token);
	new_node->left = left;
	new_node->right = right;

	return new_node;
}

static void treenode_destroy(struct treenode * node)
{
	if ( node ) {
		free(node->token);
		free(node);
	}
}

void tree_destroy(struct treenode * node)
{
	if ( node ) {
		tree_destroy(node->left);
		tree_destroy(node->right);
		treenode_destroy(node);
	}
}

void tree_print(struct treenode * node)
{
	if ( node ) {
		if ( node->token->type == TOKEN_ID ) {
			printf("%c", node->token->value.name);
		}
		else if ( node->token->type == TOKEN_OP ) {
			printf("(");
			switch ( node->token->value.type ) {
				case OP_NOT:
					printf("~");
					tree_print(node->right);
					break;

				case OP_AND:
					tree_print(node->left);
					printf("&");
					tree_print(node->right);
					break;

				case OP_OR:
					tree_print(node->left);
					printf("|");
					tree_print(node->right);
					break;
				
				default:
					fprintf(stderr, "Error: unexpected operator in tree\n");
					exit(EXIT_FAILURE);
			}
			printf(")");
		}
		else {
			fprintf(stderr, "\nError: unexpected token in tree\n");
			exit(EXIT_FAILURE);
		}
	}
}
