#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/run.h"


int is_nice_string(char *input, size_t input_length) {
    uint8_t digram_map[26 * 26] = { 0 };
    uint8_t has_sandwich = 0, has_double = 0;
    char c0 = 0, c1 = 0;

    for(size_t i = 0; i < input_length; i++) {
	char c = input[i];

	if(c1 > 0) {
	    size_t key = ((size_t)(c1 - 'a') * 26) + (c - 'a');
	    char count = ++digram_map[key];

	    if(c == c1) {
		if((c0 == c1 && count >= 3) || (c0 != c1 && count >= 2)) {
		  has_double = 1;
		}
	    } else {
		if(count >= 2) { has_double = 1; }
	    }
	}
	if(c == c0) { has_sandwich = 1; }
	
	c0 = c1;
	c1 = c;
    }

    return has_sandwich && has_double;
}

int64_t solve(char *input, size_t input_length)
{
    int64_t result = 0;

    char* line = strtok(input, "\n");
    while (line != NULL) {
	size_t line_length = strnlen(line, input_length);
	if(is_nice_string(line, line_length)) {
	    result++;
	}

        line = strtok(NULL, "\n");
    }

    return result;
}

#ifndef TESTING
int main()
{
    return run(solve);
}
#endif
