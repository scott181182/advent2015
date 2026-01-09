#ifndef BOUNDED_LIST_SET_H
#define BOUNDED_LIST_SET_H

#include <stdlib.h>

/**
 * Macro to define a type-specific bounded list-based set.
 * 
 * Usage:
 *   DEFINE_BOUNDED_LIST_SET(TypeName, ElementType, equality_func)
 * 
 * Example:
 *   DEFINE_BOUNDED_LIST_SET(Coord, Coord, coord_equals)
 * 
 * This generates:
 *   - struct BoundedListSet_TypeName
 *   - int bounded_list_set_TypeName_init(BoundedListSet_TypeName *set, size_t capacity)
 *   - void bounded_list_set_TypeName_destroy(BoundedListSet_TypeName *set)
 *   - int bounded_list_set_TypeName_add(BoundedListSet_TypeName *set, ElementType *value)
 */
#define DEFINE_BOUNDED_LIST_SET(TypeName, ElementType, EqualityFunc)         \
    typedef struct BoundedListSet_##TypeName##_s {                           \
        size_t capacity;                                                     \
        size_t length;                                                       \
        ElementType* data;                                                   \
    } BoundedListSet_##TypeName;                                             \
                                                                             \
    static inline int bounded_list_set_##TypeName##_init(                    \
            BoundedListSet_##TypeName *set, size_t capacity) {               \
        ElementType* data = malloc(capacity * sizeof(ElementType));          \
        if(data == NULL) {                                                   \
            return -1;                                                       \
        }                                                                    \
        set->capacity = capacity;                                            \
        set->length = 0;                                                     \
        set->data = data;                                                    \
        return 0;                                                            \
    }                                                                        \
                                                                             \
    static inline void bounded_list_set_##TypeName##_destroy(                \
            BoundedListSet_##TypeName *set) {                                \
        if(set != NULL && set->data != NULL) {                               \
            free(set->data);                                                 \
            set->data = NULL;                                                \
            set->length = 0;                                                 \
            set->capacity = 0;                                               \
        }                                                                    \
    }                                                                        \
                                                                             \
    static inline int bounded_list_set_##TypeName##_add(                     \
            BoundedListSet_##TypeName *set, ElementType *value) {            \
        for(size_t i = 0; i < set->length; i++) {                            \
            if(EqualityFunc(&set->data[i], value)) { return 0; }             \
        }                                                                    \
        if(set->length >= set->capacity) {                                   \
            return -1;                                                       \
        }                                                                    \
        set->data[set->length] = *value;                                     \
        set->length += 1;                                                    \
        return 0;                                                            \
    }

#endif // BOUNDED_LIST_SET_H
