#ifndef SATISFIABILITY_LEXER_H
#define SATISFIABILITY_LEXER_H

#include <stddef.h>
#include "token.h"

struct token * tokenize(const char * input);
void free_tokens(struct token * token);
void print_tokens(struct token * token);
struct token * copy_token(struct token * token);

#endif  /*  SATISFIABILITY_LEXER_H  */
