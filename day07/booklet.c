#include <stddef.h>

#include "day07/wire_set.c"

typedef enum {
    SET,
    NOT,
} UnaryGate;
typedef enum {
    AND,
    OR,
    LSHIFT,
    RSHIFT,
} BinaryGate;

/*
 * Signal Representation.
 */
typedef enum {
    VALUE,
    WIRE,
} SignalType;
typedef union {
    unsigned short value;
    Wire* wire;
} SignalValue;
typedef struct {
    SignalType type;
    SignalValue val;
} Signal;

/*
 * Instruction Representation.
 */
typedef enum {
    UNARY_OP,
    BINARY_OP,
} InstructionType;

typedef struct {
    Signal src;
    Signal dst;
    UnaryGate gate;
} UnaryOpInstruction;
typedef struct {
    Signal src1;
    Signal src2;
    Signal dst;
    BinaryGate gate;
} BinaryOpInstruction;

typedef union {
    UnaryOpInstruction unary;
    BinaryOpInstruction binary;
} InstructionOp;

typedef struct {
    InstructionType type;
    InstructionOp op;
} Instruction;

/*
 * Graph Representation.
 */
typedef struct {
    WireSet wires;
    size_t instruction_count;
    Instruction *instructions;
} Booklet;

void parse_signal(Booklet* booklet, char *str, size_t str_length, Signal *out) {
    // Check if the signal is a value or a wire.
    if(strspn(str, "0123456789") == str_length) {
        out->type = VALUE;
        out->val.value = (unsigned short)strtoul(str, NULL, 10);
    } else {
        out->type = WIRE;
        out->val.wire = wire_set_upsert(&booklet->wires, str, str_length);
    }
}
BinaryGate parse_binary_gate(char *str, char** endptr) {
    if(strncmp(str, "OR", 2) == 0) {
        *endptr = str + 2;
        return OR;
    } else if(strncmp(str, "AND", 3) == 0) {
        *endptr = str + 3;
        return AND;
    } else if(strncmp(str, "LSHIFT", 6) == 0) {
        *endptr = str + 6;
        return LSHIFT;
    } else {
        *endptr = str + 6;
        return RSHIFT;
    }
}
int parse_instruction(Booklet* booklet, char *line, size_t line_length, Instruction *out) {
    char* str_ptr;
    // Check for NOT operation.
    if(strncmp(line, "NOT ", 4) == 0) {
        out->type = UNARY_OP;
        out->op.unary.gate = NOT;

        // Find end of signal string.
        str_ptr = strchr(line + 4, ' ');
        parse_signal(booklet, line + 4, str_ptr - (line + 4), &out->op.unary.src);
        parse_signal(booklet, str_ptr + 4, line + line_length - (str_ptr + 4), &out->op.unary.dst);
        return 0;
    }

    // Parse first signal (UnaryOp.src and BinaryOp.src1 line up in memory).
    str_ptr = strchr(line, ' ');
    parse_signal(booklet, line, str_ptr - line, &out->op.unary.src);

    // Determine if this is an assign operation.
    if(strncmp(str_ptr, " -> ", 4) == 0) {
        out->type = UNARY_OP;
        out->op.unary.gate = SET;
        parse_signal(booklet, str_ptr + 4, line + line_length - (str_ptr + 4), &out->op.unary.dst);
        return 0;
    }

    // BinaryOp!
    out->type = BINARY_OP;
    out->op.binary.gate = parse_binary_gate(str_ptr + 1, &str_ptr);

    // Parse second source signal and destination.
    char* str_ptr2 = strchr(str_ptr + 1, ' ');
    parse_signal(booklet, str_ptr + 1, str_ptr2 - (str_ptr + 1), &out->op.binary.src2);
    parse_signal(booklet, str_ptr2 + 4, line + line_length - (str_ptr2 + 4), &out->op.binary.dst);

    return 0;
}
int parse_booklet(char *input, size_t input_length, Booklet *out) {
    size_t line_count = 1, i, res;
    for (i = 0; i < input_length; i++) {
        if (input[i] == '\n') {
            line_count++;
        }
    }

    out->instruction_count = line_count;
    out->instructions = (Instruction*)malloc(sizeof(Instruction) * line_count);
    if(out->instructions == NULL) {
        return 1;
    }

    // There shouldn't be more wires than instructions.
    res = wire_set_init(&out->wires, line_count + 2);
    if(res != 0) {
        return res;
    }

    i = 0;
    char *line = strtok(input, "\n");
    while (line != NULL) {
        size_t line_length = strnlen(line, input_length);
        parse_instruction(out, line, line_length, &out->instructions[i]);

        i++;
        line = strtok(NULL, "\n");
    }

    return 0;
}

void destroy_booklet(Booklet *booklet) {
    if(booklet != NULL) {
        wire_set_destroy(&booklet->wires);
        free(booklet->instructions);
        booklet->instructions = NULL;
        booklet->instruction_count = 0;
    }
}
