#include <stdio.h>
#include "lexer.h"
#include "prompt.h"

#define BUFFER_SIZE 80

int main(void)
{
    char buffer[BUFFER_SIZE];
    get_prompted_input(buffer, BUFFER_SIZE);
    printf("Input was: [%s]\n", buffer);

    struct token * tokens = tokenize(buffer);
    print_tokens(tokens);
    free_tokens(tokens);

    return 0;
}
