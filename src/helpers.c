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
#include <stddef.h>
#include <stdbool.h>

#include "helpers.h"

void
print_input_indicator(const char * input, const size_t index)
{
    static const char * prefix = ": ";
    fprintf(stderr, "%s%s\n%s", prefix, input, prefix);
    for ( size_t i = 0; i < index; ++i ) {
        fputc(' ', stderr);
    }
    fprintf(stderr, "^\n");
}

const char *
bool_string(const bool value)
{
    return value ? "true" : "false";
}
