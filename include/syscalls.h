#pragma once

#define SYS_read 	0
#define SYS_write 	1
#define SYS_open 	2
#define SYS_close 	3
#define SYS_stat 	4
#define SYS_fstat 	5
#define SYS_lstat 	6
#define SYS_exit 	60

#ifndef STDLOLI_ASM
typedef unsigned long long syscall_t;

void* syscall1(syscall_t number, void* arg);
void* syscall2(syscall_t number, void* arg1, void* arg2);
void* syscall3(syscall_t number, void* arg1, void* arg2, void* arg3);
#endif
