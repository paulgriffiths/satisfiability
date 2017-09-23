#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "prompt.h"
#include "treenode.h"
#include "parser.h"
#include "helpers.h"

#define BUFFER_SIZE 80

int main(void)
{
    char buffer[BUFFER_SIZE];
    get_prompted_input(buffer, BUFFER_SIZE);

    struct token * tokens = tokenize(buffer);
    
    if ( tokens ) {
        struct token * next = NULL;
        struct treenode * tree = get_expr(tokens, &next);

        if ( tree ) {
            printf("Tree representation: ");
            tree_print(tree);
            printf("\n");
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
