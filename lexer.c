#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "token.h"
#include "helpers.h"

struct token * tokenize(const char * input)
{
    struct token * head = NULL;
    struct token * tail = NULL;

    size_t index = 0;
    char lookahead = input[index];

    while ( lookahead != 0 ) {
        struct token * new_token = NULL;
        const char current = lookahead;
        lookahead = input[++index];

        if ( isspace(current) ) {
            continue;
        }
        else if ( isalpha(current) ) {
            new_token = make_new_token(TOKEN_ID, current);

            if ( isalpha(lookahead) ) {
                fprintf(stderr, "Error: illegal identifier '");
                
                for ( size_t i = index - 1; isalpha(input[i]); ++i ) {
                    fputc(input[i], stderr);
                }

                fprintf(stderr, "' at position %zu\n", index);
                print_input_indicator(input, index - 1);
                free_tokens(head);
                return NULL;
            }
        }
        else if ( current == '(' ) {
            new_token = make_new_token(TOKEN_LPAREN, 0);
        }
        else if ( current == ')' ) {
            new_token = make_new_token(TOKEN_RPAREN, 0);
        }
        else if ( current == '&' ) {
            new_token = make_new_token(TOKEN_OP, OP_AND);
        }
        else if ( current == '|' ) {
            new_token = make_new_token(TOKEN_OP, OP_OR);
        }
        else if ( current == '~' ) {
            new_token = make_new_token(TOKEN_OP, OP_NOT);
        }
        else {
            fprintf(stderr, "Error: unexpected character '%c' at index %zu\n",
                    current, index);
            print_input_indicator(input, index - 1);
            free_tokens(head);
            return NULL;
        }

        new_token->input_index = index;
        
        if ( head == NULL ) {
            head = tail = new_token;
        }
        else {
            tail->next = new_token;
            tail = new_token;
        }
    }

    return head;
}
