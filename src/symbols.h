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

#ifndef SATISFIABILITY_SYMBOLS_H
#define SATISFIABILITY_SYMBOLS_H

#include <stdbool.h>

#define SYMBOL_TABLE_SIZE 26

struct symbols {
    bool values[SYMBOL_TABLE_SIZE];
    bool present[SYMBOL_TABLE_SIZE];
    char names[SYMBOL_TABLE_SIZE + 1];
    char contents[SYMBOL_TABLE_SIZE + 1];
    int count;
};

void reset_symbols(struct symbols * table);
bool get_symbol_value(struct symbols * table, int key);
void set_symbol_value(struct symbols * table, int key, bool value);

#endif  /*  SATISFIABILITY_SYMBOLS_H  */
