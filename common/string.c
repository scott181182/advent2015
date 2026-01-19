#include <string.h>

#include <common/string.h>

void string_from_cstr(const char* cstr, String* out) {
    out->data = (char*)cstr;
    out->length = strlen(cstr);
}
void string_from_strn(const char* str, size_t str_length, String* out) {
    out->data = (char*)str;
    out->length = str_length;
}

int string_equals(const String* a, const String* b) {
    if(a->length != b->length) {
        return 0;
    }
    return strncmp(a->data, b->data, a->length) == 0;
}
