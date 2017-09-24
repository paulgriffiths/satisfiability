#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "symbols.h"

char * calc_symbol_names(struct symbols * table)
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

	return table->names;
}

void reset_symbols(struct symbols * table)
{
	for ( size_t i = 0; i < SYMBOL_TABLE_SIZE; ++i ) {
		table->values[i] = false;
		table->present[i] = false;
	}
	table->count = 0;
	memset(table->names, 0, SYMBOL_TABLE_SIZE + 1);
	memset(table->contents, 0, SYMBOL_TABLE_SIZE + 1);
}

bool get_symbol_value(struct symbols * table, char key)
{
    return table->values[tolower(key) - 'a'];
}

void set_symbol_value(struct symbols * table, char key, bool value)
{
    table->values[tolower(key) - 'a'] = value;
    if ( table->present[tolower(key) - 'a'] == false ) {
    	table->present[tolower(key) - 'a'] = true;
    	table->count += 1;
    }
    calc_symbol_names(table);
}

