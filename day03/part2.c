#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/run.h"

typedef struct Coord {
    uint32_t x;
    uint32_t y;
} Coord;

int coord_equals(Coord *a, Coord *b) {
    return a->x == b-> x && a->y == b->y;
}
void visit_next_coord(Coord *current, char direction) {
    switch(direction) {
	case '>': current->x += 1; break;
	case '<': current->x -= 1; break;
	case '^': current->y += 1; break;
	case 'v': current->y -= 1; break;
    }
}

typedef struct FixedSet_s {
    size_t capacity;
    size_t length;
    Coord* data;
} FixedSet;

FixedSet create_fixed_set(size_t capacity) {
    Coord* data = malloc(capacity * sizeof(Coord));
    if(data == NULL) {
	exit(1);
    }

    return (FixedSet){
	.capacity = capacity,
	.length = 0,
	.data = data
    };
}
void set_add(FixedSet *vec, Coord *value) {
    for(size_t i = 0; i < vec->length; i++) {
	if(coord_equals(&vec->data[i], value)) { return; }
    }
    vec->data[vec->length].x = value->x;
    vec->data[vec->length].y = value->y;
    vec->length += 1;
}

int64_t solve(char* input, size_t input_length) {
    Coord p_santa = { .x = 0, .y = 0 };
    Coord p_robot = { .x = 0, .y = 0 };
    FixedSet past_positions = create_fixed_set(input_length);

    set_add(&past_positions, &p_santa);
    for(size_t i = 0; i < input_length; i++){
        visit_next_coord(&p_santa, input[i]);
	set_add(&past_positions, &p_santa);

	i++;
	if(i >= input_length) { break; }

        visit_next_coord(&p_robot, input[i]);
	set_add(&past_positions, &p_robot);
    }

    free(past_positions.data);

    return past_positions.length;
}

#ifndef TESTING
int main() {
    return run(solve);
}
#endif
