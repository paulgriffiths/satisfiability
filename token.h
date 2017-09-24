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
