#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/run.h"
#include "booklet.c"

int64_t solve(char *input, size_t input_length) {
    Booklet booklet;

    int status = parse_booklet(input, input_length, &booklet);
    if(status != 0) { return -1; }

    Wire* b_wire = wire_set_upsert(&booklet.wire_set, "b", 1);
    set_wire_value(b_wire, 3176);

    propagate_signals(&booklet);
    Wire* a_wire = wire_set_upsert(&booklet.wire_set, "a", 1);
    int64_t result = a_wire->value;

    destroy_booklet(&booklet);
    return result;
}

#ifndef TESTING
int main()
{
    return run(solve);
}
#endif
