#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/run.h"
#include "instruction.c"



#define LOOP_GRID(grid, x0, y0, x1, y1, body) \
    for (uint32_t x = x0; x <= x1; x++) { \
        for (uint32_t y = y0; y <= y1; y++) body \
    }

int64_t solve(char *input, size_t input_length) {
    char grid[1000][1000] = {0};

    Instruction *instrs;
    size_t instr_count = parse_instructions(input, input_length, &instrs);

    for(size_t i = 0; i < instr_count; i++) {
        Instruction instr = instrs[i];
        LOOP_GRID(grid, instr.bounds.x0, instr.bounds.y0, instr.bounds.x1, instr.bounds.y1, {
            switch (instr.action) {
                case TurnOn:
                    grid[x][y] = 1;
                    break;
                case TurnOff:
                    grid[x][y] = 0;
                    break;
                case Toggle:
                    grid[x][y] = !grid[x][y];
                    break;
            }
        })
    }

    int64_t result = 0;

    LOOP_GRID(grid, 0, 0, 999, 999, {
        result += grid[x][y];
    })

    free(instrs);
    return result;
}

#ifndef TESTING
int main()
{
    return run(solve);
}
#endif
