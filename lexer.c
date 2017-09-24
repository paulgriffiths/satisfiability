#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "token.h"
#include "helpers.h"

static struct token * make_new_token(const enum token_type type,
                                     const int value)
{
    struct token * new_token = malloc(sizeof *new_token);
    if ( !new_token ) {
        perror("couldn't allocate memory for token");
        exit(EXIT_FAILURE);
    }

    new_token->type = type;
    new_token->next = NULL;

    if ( type == TOKEN_ID ) {
        new_token->value.name = value;
    }
    else if ( type == TOKEN_OP ) {
        new_token->value.type = value;
    }
    else {
        new_token->value.type = 0;
    }

    return new_token;
}

struct token * copy_token(struct token * token) 
{
    struct token * new_token = malloc(sizeof *new_token);
    if ( new_token == NULL ) {
        perror("couldn't allocate memory for token");
        exit(EXIT_FAILURE);
    }

    new_token->type = token->type;
    new_token->next = NULL;

    if ( token_is_id(token) ) {
        new_token->value.name = token->value.name;
    }
    else if ( token_is_operator(token) ) {
        new_token->value.type = token->value.type;
    }
    else {
        new_token->value.type = 0;
    }

    return new_token;
}

void free_tokens(struct token * token)
{
    while ( token ) {
        struct token * next = token->next;
        free(token);
        token = next;
    }
}

struct token * tokenize(const char * input)
{
    struct token * head = NULL;
    struct token * tail = NULL;

    size_t index = 0;
    char lookahead = input[index];

    while ( lookahead != 0 ) {
        const char current = lookahead;
        lookahead = input[++index];
        struct token * new_token = NULL;

        if ( isspace(current) ) {
            continue;
        }
        else if ( isalpha(current) ) {
            new_token = make_new_token(TOKEN_ID, current);

            if ( isalpha(lookahead) ) {
                printf("Illegal identifier '");
                
                for ( size_t i = index - 1; isalpha(input[i]); ++i ) {
                    putchar(input[i]);
                }

                printf("' at position %zu\n", index);
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
        else if ( current == '!' ) {
            new_token = make_new_token(TOKEN_OP, OP_NOT);
        }
        else {
            printf("Unexpected character '%c' at index %zu\n", current, index);
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
