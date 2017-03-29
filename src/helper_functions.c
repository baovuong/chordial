#include "helper_functions.h"

#include <string.h>

int find_string(int array_length, const char* array[], const char* value) {
    for (int i=0; i<array_length; i++) {
        if (strcmp(array[i], value) == 0) {
            return i;
        }
    }
    return -1;
}

int is_number(char c) {
    return strchr("0123456789", c) != NULL;
}

int is_pitch(char c) {
    return strchr("ABCDEFG", c) != NULL;
}

int is_accent(char c) {
    return strchr("#b", c) != NULL;
}