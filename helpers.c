#include <stdio.h>
#include "helpers.h"

void print_input_indicator(const char * input, const size_t index)
{
    static const char * prefix = ": ";
    printf("%s%s\n%s", prefix, input, prefix);
    for ( size_t i = 0; i < index; ++i ) {
        putchar (' ');
    }
    printf("^\n");
}
