#include <stat.h>
#include <syscalls.h>

int stat(const char* fname, stat_t* pstat) {
	return (int)(intptr_t)syscall2(SYS_stat, (void*)fname, pstat);
}

int fstat(fd_t f, stat_t* pstat) {
	return (int)(intptr_t)syscall2(SYS_fstat, (void*)f, pstat);
}

int lstat(const char* fname, stat_t* pstat) {
	return (int)(intptr_t)syscall2(SYS_lstat, (void*)fname, pstat);
}
