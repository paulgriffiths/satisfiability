#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "symbols.h"

#define KEY_INDEX(k) (tolower(k) - 'a')

static void calc_symbol_names_and_contents(struct symbols * table)
{
    memset(table->names, 0, SYMBOL_TABLE_SIZE + 1);
    memset(table->contents, 0, SYMBOL_TABLE_SIZE + 1);

    int n = 0;

    for ( size_t i = 0; i < SYMBOL_TABLE_SIZE && n < table->count; ++i ) {
        if ( table->present[i] ) {
            table->names[n] = i + 'a';
            table->contents[n++] = table->values[i] ? 'T' : 'F';
        }
    }
}

void reset_symbols(struct symbols * table)
{
    memset(table->values, false, SYMBOL_TABLE_SIZE * sizeof *table->values);
    memset(table->present, false, SYMBOL_TABLE_SIZE * sizeof *table->values);
    memset(table->names, 0, SYMBOL_TABLE_SIZE + 1);
    memset(table->contents, 0, SYMBOL_TABLE_SIZE + 1);
    table->count = 0;
}

bool get_symbol_value(struct symbols * table, int key)
{
    return table->values[KEY_INDEX(key)];
}

void set_symbol_value(struct symbols * table, int key, bool value)
{
    table->values[KEY_INDEX(key)] = value;

    if ( table->present[KEY_INDEX(key)] == false ) {
        table->present[KEY_INDEX(key)] = true;
        table->count += 1;
    }

    calc_symbol_names_and_contents(table);
}

