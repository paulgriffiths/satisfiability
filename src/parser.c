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
#include <stdbool.h>

#include "parser.h"
#include "token.h"
#include "treenode.h"

struct treenode *
get_fact(struct token * in,
         struct token ** out,
         struct symbols * table)
{
    struct token * next = in;
    struct treenode * node = NULL;

    if ( token_is_id(in) ) {
        node = treenode_create(in, NULL, NULL);
        next = in->next;
        set_symbol_value(table, in->value, false);
    }
    else if ( token_is_lparen(in) ) {
        node = get_expr(in->next, &next, table);
        if ( next && token_is_rparen(next) ) {
            next = next->next;
        }
        else {
            tree_destroy(node);
            node = NULL;
            fprintf(stderr, "Error: missing closing parenthesis\n");
        }
    }
    else {
        fprintf(stderr, "Error: missing factor\n");
    }

    *out = next;
    return node;
}

struct treenode *
get_elem(struct token * in,
         struct token ** out,
         struct symbols * table)
{
    struct token * next = in;
    struct treenode * node = NULL;
    struct treenode * second = NULL;

    if ( token_is_not(in) ) {
        second = get_fact(in->next, &next, table);
        if ( second ) {
            node = treenode_create(in, NULL, second);
            next = in->next->next;
        }
    }
    else {
        node = get_fact(in, &next, table);
    }

    *out = next;
    return node;
}

struct treenode *
get_term(struct token * in,
         struct token ** out,
         struct symbols * table)
{
    struct token * next = in;
    struct treenode * node = NULL;
    struct treenode * second = NULL;

    if ( (node = get_elem(in, &next, table)) ) {
        while ( token_is_and(next) ) {
            struct token * op_node = next;

            if ( (second = get_elem(next->next, &next, table)) ) {
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

struct treenode *
get_expr(struct token * in,
         struct token ** out,
         struct symbols * table)
{
    struct token * next = in;
    struct treenode * node = NULL;
    struct treenode * second = NULL;

    if ( (node = get_term(in, &next, table)) ) {
        while ( token_is_or(next) ) {
            struct token * op_node = next;

            if ( (second = get_term(next->next, &next, table)) ) {
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
