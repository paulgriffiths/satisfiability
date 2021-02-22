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

#include "evaluate.h"
#include "token.h"

bool
evaluate(struct treenode * tree, struct symbols * table)
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
