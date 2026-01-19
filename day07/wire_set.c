#include <stddef.h>
#include <string.h>

#include "common/bounded_list_set.h"

typedef struct {
    char* name;
    size_t name_length;
} Wire;

int wire_equals(const Wire* a, const Wire* b) {
    if(a->name_length != b->name_length) {
        return 0;
    }
    return strncmp(a->name, b->name, a->name_length) == 0;
}

typedef struct {
    Wire* data;
    size_t capacity;
    size_t length;
} WireSet;

static inline int wire_set_init(WireSet *set, size_t capacity) {
    Wire* data = malloc(capacity * sizeof(Wire));
    if(data == NULL) { return -1; }
    set->capacity = capacity;
    set->length = 0;
    set->data = data;
    return 0;
}

static inline void wire_set_destroy(WireSet *set) {
    if(set != NULL && set->data != NULL) {
        free(set->data);
        set->data = NULL;
        set->length = 0;
        set->capacity = 0;
    }
}

static inline Wire* wire_set_upsert(WireSet *set, char* name, size_t name_length) {
    size_t i;
    for(i = 0; i < set->length; i++) {
        Wire* a = &set->data[i];
        if(a->name_length == name_length && strncmp(a->name, name, name_length) == 0) {
            // Wire already exists in the set.
            // Return pointer to existing wire.
            return a;
        }
    }
    // Check that we're not exceeding capacity.
    if(set->length >= set->capacity) {
        return NULL;
    }
    set->data[set->length].name = name;
    set->data[set->length].name_length = name_length;
    set->length += 1;
    return &set->data[set->length - 1];
}
