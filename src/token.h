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

#ifndef SATISFIABILITY_TOKEN_H
#define SATISFIABILITY_TOKEN_H

#include <stddef.h>
#include <stdbool.h>

enum token_type {
    TOKEN_ID,
    TOKEN_OP,
    TOKEN_LPAREN,
    TOKEN_RPAREN
};

enum operator_type {
    OP_NOT,
    OP_AND,
    OP_OR
};

struct token {
    enum token_type type;
    int value;
    size_t input_index;
    struct token * next;
};

struct token * make_new_token(const enum token_type type,
                              const int value);
struct token * copy_token(struct token * token);
void free_tokens(struct token * token);

bool token_is_id(struct token * token);
bool token_is_operator(struct token * token);
bool token_is_not(struct token * token);
bool token_is_and(struct token * token);
bool token_is_or(struct token * token);
bool token_is_lparen(struct token * token);
bool token_is_rparen(struct token * token);

#endif  /*  SATISFIABILITY_TOKEN_H  */
