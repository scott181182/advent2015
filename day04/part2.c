#include <stdio.h>

#include "common/run.h"
#include "day04/md5.c"



#define ITERATION_LIMIT 100000000

int64_t solve(char *input, size_t input_length)
{
    int64_t result = 1;
    unsigned char format_buffer[BYTES_PER_CHUNK] = { 0 };
    MD5State output;
    
    memcpy(format_buffer, input, input_length);

    while(result < ITERATION_LIMIT) {
        sprintf(format_buffer + input_length, "%lld\0", result);
        size_t len = strlen(format_buffer);
        md5_hash(format_buffer, len, &output);

        if ((output.a & 0xffffff) == 0) {
            break;
        }

        result++;
    }

    return result;
}

#ifndef TESTING
int main()
{
    return run(solve);
}
#endif
