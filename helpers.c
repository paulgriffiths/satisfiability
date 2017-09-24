#include <stdio.h>
#include "helpers.h"

void print_input_indicator(const char * input, const size_t index)
{
    static const char * prefix = ": ";
    fprintf(stderr, "%s%s\n%s", prefix, input, prefix);
    for ( size_t i = 0; i < index; ++i ) {
        fputc(' ', stderr);
    }
    fprintf(stderr, "^\n");
}

const char * bool_string(const bool value)
{
	return value ? "true" : "false";
}
