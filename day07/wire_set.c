#include <stddef.h>
#include <string.h>

#include "common/bounded_list_set.h"
#include "common/string.h"

typedef struct {
    String name;
    unsigned short value;
    unsigned char initialized;
} Wire;

void set_wire_value(Wire* wire, unsigned short value) {
    wire->value = value;
    wire->initialized = 1;
}

typedef struct {
    Wire* wires;
    size_t capacity;
    size_t length;
} WireSet;

static inline int wire_set_init(WireSet *set, size_t capacity) {
    set->wires = malloc(capacity * sizeof(Wire));
    if(set->wires == NULL) { return -1; }
    set->capacity = capacity;
    set->length = 0;
    return 0;
}

static inline void wire_set_destroy(WireSet *set) {
    if(set != NULL && set->wires != NULL) {
        free(set->wires);
        set->wires = NULL;
        set->length = 0;
        set->capacity = 0;
    }
}

static inline Wire* wire_set_upsert(WireSet *set, char* name, size_t name_length) {
    size_t i;
    for(i = 0; i < set->length; i++) {
        Wire* a = &set->wires[i];
        if(a->name.length == name_length && strncmp(a->name.data, name, name_length) == 0) {
            // Wire already exists in the set.
            // Return pointer to existing wire.
            return a;
        }
    }
    // Check that we're not exceeding capacity.
    if(set->length >= set->capacity) {
        return NULL;
    }

    set->wires[set->length].initialized = 0;
    string_from_strn(name, name_length, &set->wires[set->length].name);
    set->length += 1;
    return &set->wires[set->length - 1];
}
