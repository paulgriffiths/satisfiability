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
#include <stdbool.h>

#include "satisfy.h"
#include "helpers.h"
#include "evaluate.h"

static void
satisfy_internal(struct treenode * tree, struct symbols * table,
                 int offset, bool * satisfied)
{
    if ( offset == table->count ) {
        const bool result = evaluate(tree, table);
        printf("%s: %s\n", table->contents, bool_string(result));
        if ( result ) {
            *satisfied = true;
        }
    }
    else {
        for ( int state = 0; state < 2; ++state ) {
            if ( state == 0 ) {
                set_symbol_value(table, table->names[offset], false);
            }
            else {
                set_symbol_value(table, table->names[offset], true);
            }
            satisfy_internal(tree, table, offset + 1, satisfied);
        }
    }
}

bool
satisfy(struct treenode * tree, struct symbols * table)
{
    bool satisfied = false;
    satisfy_internal(tree, table, 0, &satisfied);
    return satisfied;
}
