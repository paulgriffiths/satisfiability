#include <stdio.h>
#include <stdbool.h>
#include "satisfy.h"
#include "helpers.h"
#include "evaluate.h"

static void satisfy_internal(struct treenode * tree, struct symbols * table,
                             int offset, bool * satisfied)
{
    if ( offset == table->count ) {
        const bool result = evaluate(tree, table);
        printf("%s: %s\n", table->contents, bool_string(result));
        if ( result ) {
            *satisfied = true;
        }
    }
    else {
        for ( int state = 0; state < 2; ++state ) {
            if ( state == 0 ) {
                set_symbol_value(table, table->names[offset], false);
            }
            else {
                set_symbol_value(table, table->names[offset], true);
            }
            satisfy_internal(tree, table, offset + 1, satisfied);
        }
    }
}

bool satisfy(struct treenode * tree, struct symbols * table)
{
    bool satisfied = false;
    satisfy_internal(tree, table, 0, &satisfied);
    return satisfied;
}
