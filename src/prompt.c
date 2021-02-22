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
#include <string.h>
#include "prompt.h"

static const char * prompt = "> ";

char *
get_prompted_input(char * buffer, const size_t length)
{
    printf("%s", prompt);
    fflush(stdout);

    if ( fgets(buffer, length, stdin) == NULL ) {
        return NULL;
    }

    const size_t input_length = strlen(buffer);

    if ( input_length == 0 ) {
        return NULL;
    }

    if ( buffer[input_length - 1] == '\n' ) {
        buffer[input_length - 1] = '\0';
    }
    else {
        while ( getchar() != '\n' ) {
            continue;
        }
    }

    return buffer;
}
