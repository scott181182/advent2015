#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/run.h"
#include "booklet.c"



#define LOOP_GRID(grid, x0, y0, x1, y1, body) \
    for (uint32_t x = x0; x <= x1; x++) { \
        for (uint32_t y = y0; y <= y1; y++) body \
    }

int64_t solve(char *input, size_t input_length) {
    Booklet booklet;

    int status = parse_booklet(input, input_length, &booklet);
    if(status != 0) { return -1; }

    int64_t result = 0;

    destroy_booklet(&booklet);
    return result;
}

#ifndef TESTING
int main()
{
    return run(solve);
}
#endif
