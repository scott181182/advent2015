#include <stdio.h>
#include <string.h>

#include "common/run.h"

typedef struct Box {
    uint32_t length;
    uint32_t width;
    uint32_t height;
} Box;

Box parse_box(char* input) {
    Box box = {0, 0, 0};
    sscanf(input, "%ux%ux%u", &box.length, &box.width, &box.height);
    return box;
}

int64_t paper_needed(Box box) {
    int64_t side1 = box.length * box.width;
    int64_t side2 = box.width * box.height;
    int64_t side3 = box.height * box.length;

    int64_t smallest_side = side1;
    if (side2 < smallest_side) {
        smallest_side = side2;
    }
    if (side3 < smallest_side) {
        smallest_side = side3;
    }

    return 2 * side1 + 2 * side2 + 2 * side3 + smallest_side;
}

int64_t solve(char* input, size_t input_length) {
    int64_t total = 0;

    char* line = strtok(input, "\n");
    while (line != NULL) {
        Box box = parse_box(line);
        total += paper_needed(box);
        line = strtok(NULL, "\n");
    }

    return total;
}

#ifndef TESTING
int main() {
    return run(solve);
}
#endif
