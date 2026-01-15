#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/run.h"


int is_nice_string(char *input, size_t input_length) {
    uint8_t vowel_count = 0;
    uint8_t has_double = 0;
    char last_char = 0;

    for(size_t i = 0; i < input_length; i++) {
	char c = input[i];
	
	if(
	    (c == 'b' && last_char == 'a') ||
	    (c == 'd' && last_char == 'c') ||
	    (c == 'q' && last_char == 'p') ||
	    (c == 'y' && last_char == 'x')
	) {
	    return 0;
	}

	if(c == last_char) { has_double = 1; }
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
	    vowel_count++;
	}
	last_char = c;
    }

    return vowel_count >= 3 && has_double;
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
