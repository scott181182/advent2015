#include <stdio.h>
#include <stdlib.h>

size_t read_file_to_string(const char *filename, char** out_buffer) {
    FILE *file = fopen(filename, "rb");
    size_t length;

    if (!file) return 0;

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return 0;
    }
    long seek_length = ftell(file);
    if (seek_length < 0) {
        fclose(file);
        return 0;
    }
    length = (size_t)seek_length;
    rewind(file);

    *out_buffer = (char *)malloc(length + 1);
    if (!*out_buffer) {
        fclose(file);
        return 0;
    }

    if (fread(*out_buffer, 1, length, file) != length) {
        free(*out_buffer);
        fclose(file);
        return 0;
    }
    (*out_buffer)[length] = '\0';

    fclose(file);
    return length;
}