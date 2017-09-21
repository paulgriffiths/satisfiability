#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "prompt.h"

static const char * prompt = "> ";

char * get_prompted_input(char * buffer, const size_t length)
{
    printf("%s", prompt);
    fflush(stdout);

    if ( fgets(buffer, length, stdin) == NULL ) {
        return NULL;
    }

    const size_t input_length = strlen(buffer);

    if ( input_length == 0 ) {
        return NULL;
    }

    if ( buffer[input_length - 1] == '\n' ) {
        buffer[input_length - 1] = '\0';
    }
    else {
        while ( getchar() != '\n' ) {
            continue;
        }
    }

    return buffer;
}
