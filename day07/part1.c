#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/run.h"
#include "booklet.c"

int is_fully_propagated(Booklet* booklet) {
    for(size_t i = 0; i < booklet->wire_set.length; i++) {
        Wire* wire = &booklet->wire_set.wires[i];
        if(!wire->initialized) {
            return 0;
        }
    }
    return 1;
}

void execute_unary_instruction(UnaryGate gate, unsigned short value, Wire* destination) {
    switch(gate) {
        case SET:
            set_wire_value(destination, value);
            break;
        case NOT:
            set_wire_value(destination, ~value);
            break;
        default:
            // Unknown gate.
            break;
    }
}

void execute_binary_instruction(BinaryGate gate, unsigned short a, unsigned short b, Wire* destination) {
    switch(gate) {
        case AND:
            set_wire_value(destination, a & b);
            break;
        case OR:
            set_wire_value(destination, a | b);
            break;
        case LSHIFT:
            set_wire_value(destination, a << b);
            break;
        case RSHIFT:
            set_wire_value(destination, a >> b);
            break;
        default:
            // Unknown gate.
            break;
    }
}

void propagate_signals(Booklet* booklet) {
    while(!is_fully_propagated(booklet)) {
        for(size_t i = 0; i < booklet->instruction_count; i++) {
            Instruction* instr = &booklet->instructions[i];

            // Destination signal is the same location for both Unary and Binary ops.
            // Destination signals are always wires.
            Wire* dst_wire = instr->op.unary.dst.val.wire;

            if(dst_wire->initialized) {
                // Destination wire already has a value.
                continue;
            }

            // Check if we can initialize the destination wire (if sources are initialized).
            if(instr->type == UNARY_OP) {
                Signal *src = &instr->op.unary.src;
                if(src->type == VALUE) {
                    execute_unary_instruction(instr->op.unary.gate, src->val.value, dst_wire);
                } else if(src->type == WIRE && src->val.wire->initialized) {
                    execute_unary_instruction(instr->op.unary.gate, src->val.wire->value, dst_wire);
                }
            } else {
                // Binary Op!
                Signal *src1 = &instr->op.binary.src1;
                Signal *src2 = &instr->op.binary.src2;

                if(src1->type == VALUE && src2->type == VALUE) {
                    execute_binary_instruction(instr->op.binary.gate, src1->val.value, src2->val.value, dst_wire);
                } else if(src1->type == VALUE && src2->type == WIRE && src2->val.wire->initialized) {
                    execute_binary_instruction(instr->op.binary.gate, src1->val.value, src2->val.wire->value, dst_wire);
                } else if(src1->type == WIRE && src1->val.wire->initialized && src2->type == VALUE) {
                    execute_binary_instruction(instr->op.binary.gate, src1->val.wire->value, src2->val.value, dst_wire);
                } else if(
                    src1->type == WIRE && src1->val.wire->initialized &&
                    src2->type == WIRE && src2->val.wire->initialized
                ) {
                    execute_binary_instruction(instr->op.binary.gate, src1->val.wire->value, src2->val.wire->value, dst_wire);
                }
            }
        }
    }
}

int64_t solve(char *input, size_t input_length) {
    Booklet booklet;

    int status = parse_booklet(input, input_length, &booklet);
    if(status != 0) { return -1; }

    propagate_signals(&booklet);
    Wire* out_wire = wire_set_upsert(&booklet.wire_set, "a", 1);
    int64_t result = out_wire->value;

    destroy_booklet(&booklet);
    return result;
}

#ifndef TESTING
int main()
{
    return run(solve);
}
#endif
