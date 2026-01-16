#include <stddef.h>
#include <stdint.h>



typedef enum {
    TurnOn = 0,
    TurnOff = 1,
    Toggle = 2,
} Action;

typedef struct {
    uint32_t x0;
    uint32_t y0;
    uint32_t x1;
    uint32_t y1;
} Bounds;

typedef struct {
    Action action;
    Bounds bounds;
} Instruction;

size_t parse_action(char *line, Action *out)
{
    if (strncmp(line, "turn on ", 8) == 0) {
        *out = TurnOn;
        return 8;
    }
    else if (strncmp(line, "turn off ", 9) == 0) {
        *out = TurnOff;
        return 9;
    }
    else {
        *out = Toggle;
        return 7;
    }
}
void parse_bounds(char *line, size_t line_length, Bounds *out) {
    char *str_ptr;

    out->x0 = (uint32_t)strtoul(line, &str_ptr, 10);
    out->y0 = (uint32_t)strtoul(str_ptr + 1, &str_ptr, 10);

    // Skip " through "
    str_ptr = strchr(str_ptr + 1, ' ');

    out->x1 = (uint32_t)strtoul(str_ptr + 1, &str_ptr, 10);
    out->y1 = (uint32_t)strtoul(str_ptr + 1, &str_ptr, 10);
}

void parse_instruction(char *line, size_t line_length, Instruction *out) {
    size_t bound_idx = parse_action(line, &out->action);
    parse_bounds(line + bound_idx, line_length - bound_idx, &out->bounds);
}

size_t parse_instructions(char *input, size_t input_length, Instruction** out) {
    size_t line_count = 0, i;
    for (i = 0; i < input_length; i++) {
        if (input[i] == '\n') {
            line_count++;
        }
    }

    *out = (Instruction*)malloc(line_count * sizeof(Instruction));

    i = 0;
    char *line = strtok(input, "\n");
    while (line != NULL) {
        size_t line_length = strnlen(line, input_length);
        parse_instruction(line, line_length, &(*out)[i]);

        i++;
        line = strtok(NULL, "\n");
    }

    return line_count;
}
