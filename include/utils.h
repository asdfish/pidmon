#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

extern unsigned int int_string_length(int input);
extern bool string_is_int(const char* string);
extern int string_to_int(const char* string, int* output);

#endif
