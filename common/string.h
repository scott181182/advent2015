#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#include <stddef.h>

typedef struct {
    char* data;
    size_t length;
} String;

void string_from_cstr(const char* cstr, String* out);
void string_from_strn(const char* str, size_t str_length, String* out);

int string_equals(const String* a, const String* b);

#endif //COMMON_STRING_H
