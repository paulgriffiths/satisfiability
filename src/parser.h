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

#ifndef SATISFIABILITY_PARSER_H
#define SATISFIABILITY_PARSER_H

#include "token.h"
#include "treenode.h"
#include "symbols.h"

struct treenode * get_expr(struct token * in,
        struct token ** out, struct symbols * table);
struct treenode * get_term(struct token * in,
        struct token ** out, struct symbols * table);
struct treenode * get_elem(struct token * in,
        struct token ** out, struct symbols * table);
struct treenode * get_fact(struct token * in,
        struct token ** out, struct symbols * table);

#endif  /*  SATISFIABILITY_PARSER_H  */
