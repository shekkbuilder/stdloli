#include <stdloli.h>

void memset(void* p, uint8_t val, size_t count) {
	uint8_t* b = (uint8_t*)p;
	for (; count; count--) {
		*(b++) = val;
	}
}

void memcpy(void* dst, const void* src, size_t count) {
	uint8_t* d = dst;
	const uint8_t* s = src;
	for (; count; count--) {
		*(d++) = *(s++);
	}
}
