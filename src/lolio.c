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
