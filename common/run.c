#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "run.h"

#define INPUT_BUFFER_SIZE 4096

int run(int64_t (*solve_fn)(char *input, size_t input_length)) {
    char input_buffer[INPUT_BUFFER_SIZE];

    char* ret = malloc(sizeof(char));
    if (ret == NULL) {
        printf("Input memory allocation failed\n");
        return 1;
    }
    ret[0] = '\0';
    size_t ret_length = 0;
    
    while(fgets(input_buffer, INPUT_BUFFER_SIZE, stdin) != NULL) {
        size_t input_length = strlen(input_buffer);

        ret = realloc(ret, (ret_length + input_length + 1) * sizeof(char));
        if (ret == NULL) {
            printf("Input memory reallocation failed\n");
            return 1;
        }

        memcpy(ret + ret_length, input_buffer, input_length);
        ret_length += input_length;
        ret[ret_length] = '\0';
    }

    size_t input_length = strlen(input_buffer);
    if (input_length == 0) {
        printf("No input provided\n");
        return 1;
    } else if(input_length == INPUT_BUFFER_SIZE - 1) {
        printf("Input too long\n");
        return 1;
    }

    int64_t result = solve_fn(ret, ret_length);
    free(ret);
    printf("%ld\n", result);
    return 0;
}