#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"

static struct token * make_new_token(const enum token_type type,
                                     const int value)
{
    struct token * new_token = malloc(sizeof *new_token);
    if ( new_token == NULL ) {
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

void free_tokens(struct token * token)
{
    struct token * current = token;

    while ( current ) {
        struct token * next = current->next;
        free(current);
        current = next;
    }
}

static void print_input_indicator(const char * input, const size_t index)
{
    static const char * prefix = ": ";
    printf("%s%s\n%s", prefix, input, prefix);
    for ( size_t i = 0; i < index; ++i ) {
        putchar (' ');
    }
    printf("^\n");
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

void print_tokens(struct token * token)
{
    int num_tokens = 0;

    while ( token ) {
        switch ( token->type ) {
            case TOKEN_ID:
                printf("Token: identifier '%c'\n", token->value.name);
                break;

            case TOKEN_LPAREN:
                printf("Token: opening parenthesis\n");
                break;

            case TOKEN_RPAREN:
                printf("Token: closing parenthesis\n");
                break;

            case TOKEN_OP:
                printf("Token: ");
                switch ( token->value.type ) {
                    case OP_AND:
                        printf("AND operator\n");
                        break;

                    case OP_OR:
                        printf("OR operator\n");
                        break;

                    case OP_NOT:
                        printf("NOT operator\n");
                        break;

                    default:
                        printf("Unrecognized operator!\n");
                        exit(EXIT_FAILURE);
                }
                break;

            default:
                printf("Unrecognized token!\n");
                exit(EXIT_FAILURE);
        }

        token = token->next;
        ++num_tokens;
    }

    printf("%d tokens in total.\n", num_tokens);
}

