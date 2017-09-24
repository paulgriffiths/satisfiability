#ifndef SATISFIABILITY_SYMBOLS_H
#define SATISFIABILITY_SYMBOLS_H

#include <stdbool.h>

#define SYMBOL_TABLE_SIZE 26

struct symbols {
	bool values[SYMBOL_TABLE_SIZE];
	bool present[SYMBOL_TABLE_SIZE];
	char names[SYMBOL_TABLE_SIZE + 1];
	char contents[SYMBOL_TABLE_SIZE + 1];
	int count;
};

void reset_symbols(struct symbols * table);
bool get_symbol_value(struct symbols * table, int key);
void set_symbol_value(struct symbols * table, int key, bool value);

#endif	/*  SATISFIABILITY_SYMBOLS_H  */
