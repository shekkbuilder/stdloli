#include <string.h>
#include <math.h>

size_t strlen(const char *str) {
	const char *p;
	for (p = str; *p; p++);
	return p - str;
}

char toupper(char c) {
	return (c >= 'a' && c <= 'z') ? c - 0x20 : c;
}

char tolower(char c) {
	return (c >= 'A' && c <= 'Z') ? c + 0x20 : c;
}

size_t itoa(uint8_t base, int64_t val, char* buf, size_t width, char filler) {
	if (base <= 0) {
		return 0;
	}

	if (val < 0) {
		*(buf++) = '-';
	}

	val = abs(val);
	char* p = buf;
	do {
		uint8_t digit = val % base;
		val /= base;
		*(p++) = "0123456789abcdef"[digit];
	} while(val);

	while (p - buf < width) {
		*(p++) = filler;
	}

	size_t res = p - buf;
	p--;

	char c;
	while (p > buf) { /* flip the string */
		c = *p;
		*(p--) = *buf;
		*(buf++) = c;
	}

	return res;
}
