#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "prompt.h"
#include "treenode.h"
#include "parser.h"
#include "helpers.h"
#include "symbols.h"
#include "evaluate.h"

#define BUFFER_SIZE 80

void satisfy(struct treenode * tree, struct symbols * table, int offset);

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
            printf("Tree representation: ");
            tree_print(tree);
            printf("\n");
            
            printf("%s\n", table.names);
            for ( int i = 0; i < table.count; ++i ) {
                putchar('-');
            }
            putchar('\n');

            satisfy(tree, &table, 0);

            tree_destroy(tree);
        }
        else { 
            size_t index;
            if ( next ) {
                index = next->input_index;
            }
            else {
                index = strlen(buffer);
            }
            print_input_indicator(buffer, index);
        }

        free_tokens(tokens);
    }

    return 0;
}

void satisfy(struct treenode * tree, struct symbols * table, int offset)
{
    if ( offset == table->count ) {
        printf("%s: %s\n", table->contents, bool_string(evaluate(tree, table)));
    }
    else {
        for ( int state = 0; state < 2; ++state ) {
            if ( state == 0 ) {
                set_symbol_value(table, table->names[offset], false);
            }
            else {
                set_symbol_value(table, table->names[offset], true);
            }
            satisfy(tree, table, offset + 1);
        }
    }
}
