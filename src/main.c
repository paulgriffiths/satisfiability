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
#include <string.h>

#include "lexer.h"
#include "prompt.h"
#include "treenode.h"
#include "parser.h"
#include "helpers.h"
#include "symbols.h"
#include "satisfy.h"
#include "options.h"

#define BUFFER_SIZE 80

int
main(int argc, char ** argv)
{
    process_options(argc, argv);

    char buffer[BUFFER_SIZE];
    get_prompted_input(buffer, BUFFER_SIZE);

    struct token * tokens = tokenize(buffer);
    
    if ( tokens ) {
        struct token * next = NULL;
        struct symbols table;
        reset_symbols(&table);
        struct treenode * tree = get_expr(tokens, &next, &table);

        if ( tree && next == NULL ) {
            printf("%s\n", table.names);
            for ( int i = 0; i < table.count; ++i ) {
                putchar('=');
            }
            putchar('\n');

            if ( satisfy(tree, &table) ) {
                printf("Formula is satisfiable\n");
            }
            else {
                printf("Formula is not satisfiable\n");
            }
            tree_destroy(tree);
        }
        else {
            if ( tree ) {
                fprintf(stderr, "Error: extraneous input / missing operator\n"); 
            }
            size_t index = next ? next->input_index - 1 : strlen(buffer);
            print_input_indicator(buffer, index);
        }

        free_tokens(tokens);
    }

    return 0;
}
