#ifndef SATISFIABILITY_LEXER_H
#define SATISFIABILITY_LEXER_H

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
    union {
        char name;
        enum operator_type type;
    } value;
    struct token * next;
};

struct token * tokenize(const char * input);
void free_tokens(struct token * token);
void print_tokens(struct token * token);

#endif  /*  SATISFIABILITY_LEXER_H  */
