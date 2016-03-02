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
		int valid = 0; /* true if there's at least one specifier */
		int base = 0;
		int string = 0;
		int chara = 0;
		int integer = 0;
		int longi = 0;
		int uppercase = 0;
		int unsig = 0;
		
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
				longi = 1;
				integer = 1;
				break;

			case 'd':
			case 'x':
			case 'o':
				base = bases[lc - 'd'];
				integer = 1;
				break;

			case 'u':
				unsig = 1;	
				integer = 1;
				break;

			case 'c':
				chara = 1;
				break;

			case 's':
				string = 1;
				break;

			case 0:
			default:
				done = 1;
				continue;
			}

			uppercase = tolower(*f) != *f; 
			f++;
			valid = 1;
		}

		if (!valid) {
			f = start;
			goto skipchar;
		}

		/* actually do the formatting */
		size_t charcount = 0;
		#define printf_itoa(T) \
			itoa(base, (int64_t)(T)va_arg(va, T), p, width, fill)
		#define	printf_itoa_s(T) \
			(unsig ? printf_itoa(u##T) : printf_itoa(T))

		if (integer && !base) {
			base = 10;
		}
	
		if (string) {
			const char* s = (const char*)va_arg(va, const char*);
			charcount = strlen(s);
			memcpy(p, s, charcount);
		}

		else if (chara) {
			charcount = 1;
			*p = (char)va_arg(va, int);
		}

		else {
			charcount = longi ?
				printf_itoa_s(int64_t) :
				printf_itoa_s(int32_t);
		}

		if (uppercase) { 
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
