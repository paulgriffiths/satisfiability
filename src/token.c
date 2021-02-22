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
#include <stdlib.h>
#include <stdbool.h>

#include "token.h"

struct token *
make_new_token(const enum token_type type,
               const int value)
{
    struct token * new_token = malloc(sizeof *new_token);
    if ( !new_token ) {
        perror("couldn't allocate memory for token");
        exit(EXIT_FAILURE);
    }

    new_token->type = type;
    new_token->value = value;
    new_token->input_index = 0;
    new_token->next = NULL;

    return new_token;
}

struct token *
copy_token(struct token * token) 
{
    return make_new_token(token->type, token->value);
}

void
free_tokens(struct token * token)
{
    while ( token ) {
        struct token * next = token->next;
        free(token);
        token = next;
    }
}

bool
token_is_id(struct token * token)
{
    if ( token ) {
        return token->type == TOKEN_ID;
    }
    else {
        return false;
    }
}

bool
token_is_operator(struct token * token)
{
    if ( token ) {
        return token->type == TOKEN_OP;
    }
    else {
        return false;
    }
}

bool
token_is_not(struct token * token)
{
    if ( token ) {
        return (token->type == TOKEN_OP) && (token->value == OP_NOT);
    }
    else {
        return false;
    }
}

bool
token_is_and(struct token * token)
{
    if ( token ) {
        return (token->type == TOKEN_OP) && (token->value == OP_AND);
    }
    else {
        return false;
    }
}

bool
token_is_or(struct token * token)
{
    if ( token ) {
        return (token->type == TOKEN_OP) && (token->value == OP_OR);
    }
    else {
        return false;
    }
}

bool
token_is_lparen(struct token * token)
{
    if ( token ) {
        return token->type == TOKEN_LPAREN;
    }
    else {
        return false;
    }
}

bool
token_is_rparen(struct token * token)
{
    if ( token ) {
        return token->type == TOKEN_RPAREN;
    }
    else {
        return false;
    }
}
