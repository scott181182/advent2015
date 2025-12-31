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

int64_t ribbon_needed(Box box) {
    uint32_t side0, side1;

    // Identify longest side to determine the two shortest sides.
    if (box.length >= box.width && box.length >= box.height) {
        side0 = box.width;
        side1 = box.height;
    } else if (box.width >= box.length && box.width >= box.height) {
        side0 = box.length;
        side1 = box.height;
    } else {
        side0 = box.length;
        side1 = box.width;
    }

    int64_t perimeter = 2 * side0 + 2 * side1;
    int64_t volume = box.length * box.width * box.height;

    return perimeter + volume;
}

int64_t solve(char* input, size_t input_length) {
    int64_t total = 0;

    char* line = strtok(input, "\n");
    while (line != NULL) {
        Box box = parse_box(line);
        total += ribbon_needed(box);
        line = strtok(NULL, "\n");
    }

    return total;
}

#ifndef TESTING
int main() {
    return run(solve);
}
#endif
