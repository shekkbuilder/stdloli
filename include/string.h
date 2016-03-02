#pragma once

#include <lolint.h>

size_t strlen(const char *str);
char toupper(char c);
char tolower(char c);
size_t itoa(uint8_t base, int64_t val, char* buf, size_t width, char filler);
