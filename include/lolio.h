#pragma once

#include <types.h>
#include <stdloli.h>

#define null ((void*)0)

#define stdin	0
#define stdout	1
#define stderr	2

#define o_ronly		00
#define o_wonly		01
#define o_rw		02
#define	o_excl		0200		/* error if already exists */
#define	o_trunc		01000		/* truncate to zero length */

fd_t fmake(const char* fname, uint16_t flags, uint16_t mode);
fd_t fopen(const char* fname, uint16_t flags);
void fclose(fd_t fd);
size_t fwrite(fd_t fd, const void* data, size_t byte_count);
size_t fread(fd_t fd, void* dst, size_t byte_count);
size_t fputs(fd_t fd, const char* str);
size_t puts(const char* str);
size_t prln(const char* str);
size_t sprintf(char*buf, const char* fmt, ...);
size_t vsprintf(char* buf, const char* fmt, va_list va);
