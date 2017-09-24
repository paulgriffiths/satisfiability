#ifndef SATISFIABILITY_SYMBOLS_H
#define SATISFIABILITY_SYMBOLS_H

#include <stdbool.h>

#define SYMBOL_TABLE_SIZE 26

struct symbols {
	bool values[SYMBOL_TABLE_SIZE];
	bool present[SYMBOL_TABLE_SIZE];
	int count;
	char names[SYMBOL_TABLE_SIZE + 1];
	char contents[SYMBOL_TABLE_SIZE + 1];
};

void reset_symbols(struct symbols * table);
bool get_symbol_value(struct symbols * table, char key);
void set_symbol_value(struct symbols * table, char key, bool value);
char * calc_symbol_names(struct symbols * table);

#endif	/*  SATISFIABILITY_SYMBOLS_H  */
