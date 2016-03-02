#include <lolio.h>
#include <string.h>
#include <syscalls.h>

#define	o_creat	0100 /* create if nonexistant */

fd_t fmake(const char* fname, uint16_t flags, uint16_t mode) {
	flags |= o_creat;
	return (fd_t)syscall3(SYS_open, 
			(void*)fname, 
			(void*)(uintptr_t)flags, 
			(void*)(uintptr_t)mode);
}

fd_t fopen(const char* fname, uint16_t flags) {
	return (fd_t)syscall2(SYS_open, 
			(void*)fname, 
			(void*)(uintptr_t)flags);
}

void fclose(fd_t fd) {
	syscall1(SYS_close, (void*)fd);
}

size_t fwrite(fd_t fd, const void* data, size_t byte_count) {
	return (size_t)syscall3(SYS_write, 
			(void*)fd, 
			(void*)data, 
			(void*)byte_count);
}

size_t fread(fd_t fd, void* dst, size_t byte_count) {
	return (size_t)syscall3(SYS_read, 
			(void*)fd, 
			dst, 
			(void*)byte_count);
}

size_t fputs(fd_t fd, const char* str) {
	return fwrite(fd, str, strlen(str));
}

size_t puts(const char* str) {
	return fputs(stdout, str);
}

size_t prln(const char* str) {
	return puts(str) + puts("\n");
}

static inline int digit(char c) {
	return c >= '0' && c <= '9';
}

/* shitcode ahead */
size_t vsprintf(char* buf, const char* fmt, va_list va) {
	char* p = buf;
	const char* f = fmt;
	const char* start = f; /* position of the last % char */
	while (*f) {
		if (*f != '%') {
			goto skipchar; /* I'm evil */
		}

		if (*(f+1) == '%') {
			/* escape with %% */
			goto skipchar;
		}

		start = f;

		/* zero-fill */
		char fill = ' ';
		int width = 0;
		if (*(++f) == '0') {
			fill = '0';
			f++;

			/* if we specify zero fill, the next specifier must be width */
			if (!digit(*f)) {
				f--;
				goto skipchar;
			}
		}

		/* width can also be specified without the zero-fill specifier */
		if (fill != ' ' || digit(*f)) {
			width = *(f++) - '0';
		}

		/* process all specifiers */
		int done = 0;
		uint8_t flags = 0;
		int base = 0;
		static const uint32_t 
			valid = 	1 << 0, /* true if there's at least one specifier */
			string = 	1 << 1,
			chara = 	1 << 2,
			integer = 	1 << 3,
			longi = 	1 << 4,
			uppercase = 1 << 5,
			unsig = 	1 << 6;
		
		/* just because using a normal switch is boring */
		static const int bases[21] = { 
			[0] = 10, 
			[11] = 8,
			[20] = 16,
		};

		char lc;
		while (!done) {
			switch (lc = tolower(*f)) {
			case 'l':
				flags |= longi | integer;
				break;

			case 'd':
			case 'x':
			case 'o':
				base = bases[lc - 'd'];
				flags |= integer;
				break;

			case 'u':
				flags |= unsig | integer;
				break;

			case 'c':
				flags |= chara;
				break;

			case 's':
				flags |= string;
				break;

			case 0:
			default:
				done = 1;
				continue;
			}

			if (tolower(*f) != *f) {
				flags |= uppercase;
			}
			f++;
			flags |= valid;
		}

		if (!(flags & valid)) {
			f = start;
			goto skipchar;
		}

		/* actually do the formatting */
		size_t charcount = 0;
		#define printf_itoa(T) \
			itoa(base, (int64_t)(T)va_arg(va, T), p, width, fill)
		#define	printf_itoa_s(T) \
			(flags & unsig ? printf_itoa(u##T) : printf_itoa(T))

		if (flags & integer && !base) {
			base = 10;
		}
	
		if (flags & string) {
			const char* s = (const char*)va_arg(va, const char*);
			charcount = strlen(s);
			memcpy(p, s, charcount);
		}

		else if (flags & chara) {
			charcount = 1;
			*p = (char)va_arg(va, int);
		}

		else {
			charcount = flags & longi ?
				printf_itoa_s(int64_t) :
				printf_itoa_s(int32_t);
		}

		if (flags & uppercase) { 
			/* this could be optimized when we're dealing with integers by 
			 * only doing anything if it's a hex number */
			for (; charcount; charcount--) {
				*p = toupper(*p);
				p++;
			}
		} else {
			p += charcount;
		}

		continue;

skipchar: /* ghetto way to avoid writing the same code over and over */
		*(p++) = *(f++);
	}

	*p = 0;
	return p - buf;
}

size_t sprintf(char*buf, const char* fmt, ...) {
	size_t res;
	va_list va;
	va_start(va, fmt);
	res = vsprintf(buf, fmt, va);
	va_end(va);
	return res;
}
