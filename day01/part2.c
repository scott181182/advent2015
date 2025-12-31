#include <stdio.h>

#include "common/run.h"

int64_t solve(char* input, size_t input_length) {
    int64_t total = 0;

    for (unsigned long i = 0; i < input_length; i++) {
        char current_char = input[i];
        switch (current_char) {
            case '(': total += 1; break;
            case ')': total -= 1; break;
            default: {
                printf("Malformed input: unexpected character '%c'\n", current_char);
                return 1;
            }
        }

        if(total == -1) {
            return i + 1;
        }
    }

    printf("Could not reach basement\n");
    return -1;
}

#ifndef TESTING
int main() {
    return run(solve);
}
#endif
