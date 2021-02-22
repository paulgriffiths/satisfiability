/*  SATISY, a solver of the satisfiability problem of formulae in the
 *  propositional calculus.
 *  Copyright (C) 2017-present Paul Griffiths.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include "treenode.h"

struct treenode *
treenode_create(struct token * token,
                struct treenode * left,
                struct treenode * right)
{
    struct treenode * new_node = malloc(sizeof *new_node);
    if ( !new_node ) {
        perror("couldn't allocate memory for treenode");
        exit(EXIT_FAILURE);
    }

    new_node->token = copy_token(token);
    new_node->left = left;
    new_node->right = right;

    return new_node;
}

void
tree_destroy(struct treenode * node)
{
    if ( node ) {
        tree_destroy(node->left);
        tree_destroy(node->right);
        free(node->token);
        free(node);
    }
}

void
tree_print(struct treenode * node)
{
    if ( node ) {
        struct token * token = node->token;

        if ( token_is_id(token) ) {
            printf("%c", token->value);
        }
        else if ( token_is_operator(token) ) {
            printf("(");

            if ( token_is_not(token) ) {
                printf("~");
                tree_print(node->right);
            }
            else if ( token_is_and(token) ) {
                tree_print(node->left);
                printf("&");
                tree_print(node->right);
            }
            else if ( token_is_or(token) ) {
                tree_print(node->left);
                printf("|");
                tree_print(node->right);
            }
            else {
                fprintf(stderr, "\nError: unexpected operator in tree\n");
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
