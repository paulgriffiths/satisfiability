#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "prompt.h"
#include "treenode.h"
#include "parser.h"
#include "helpers.h"
#include "symbols.h"
#include "satisfy.h"

#define BUFFER_SIZE 80

int main(void)
{
    char buffer[BUFFER_SIZE];
    get_prompted_input(buffer, BUFFER_SIZE);

    struct token * tokens = tokenize(buffer);
    
    if ( tokens ) {
        struct token * next = NULL;
        struct symbols table;
        reset_symbols(&table);
        struct treenode * tree = get_expr(tokens, &next, &table);

        if ( tree ) {
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
            size_t index = next ? next->input_index : strlen(buffer);
            print_input_indicator(buffer, index);
        }

        free_tokens(tokens);
    }

    return 0;
}
