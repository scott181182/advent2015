#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/bounded_list_set.h"
#include "common/run.h"

typedef struct Coord
{
    uint32_t x;
    uint32_t y;
} Coord;

int coord_equals(Coord *a, Coord *b)
{
    return a->x == b->x && a->y == b->y;
}
void visit_next_coord(Coord *current, char direction)
{
    switch (direction)
    {
    case '>':
        current->x += 1;
        break;
    case '<':
        current->x -= 1;
        break;
    case '^':
        current->y += 1;
        break;
    case 'v':
        current->y -= 1;
        break;
    }
}

DEFINE_BOUNDED_LIST_SET(coord, Coord, coord_equals)

int64_t solve(char *input, size_t input_length)
{
    Coord p_santa = {.x = 0, .y = 0};
    Coord p_robot = {.x = 0, .y = 0};
    BoundedListSet_coord past_positions;

    if (bounded_list_set_coord_init(&past_positions, input_length) != 0)
    {
        return -1;
    }

    bounded_list_set_coord_add(&past_positions, &p_santa);
    for (size_t i = 0; i < input_length; i++)
    {
        visit_next_coord(&p_santa, input[i]);
        bounded_list_set_coord_add(&past_positions, &p_santa);

        i++;
        if (i >= input_length)
        {
            break;
        }

        visit_next_coord(&p_robot, input[i]);
        bounded_list_set_coord_add(&past_positions, &p_robot);
    }

    int64_t result = past_positions.length;
    bounded_list_set_coord_destroy(&past_positions);

    return result;
}

#ifndef TESTING
int main()
{
    return run(solve);
}
#endif
