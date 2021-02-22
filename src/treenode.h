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

#ifndef SATISFIABILITY_TREENODE_H
#define SATISFIABILITY_TREENODE_H

#include <stdbool.h>

#include "token.h"

struct treenode {
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
