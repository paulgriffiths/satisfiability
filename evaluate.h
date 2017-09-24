#ifndef SATISFIABILITY_EVALUATE_H
#define SATISFIABILITY_EVALUATE_H

#include <stdbool.h>
#include "treenode.h"
#include "symbols.h"

bool evaluate(struct treenode * tree, struct symbols * table);

#endif  /*  SATISFIABILITY_EVALUATE_H  */
