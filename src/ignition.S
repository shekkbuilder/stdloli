#define STDLOLI_ASM
#include <syscalls.h>

.intel_syntax noprefix
.text
	/* ignition */
	.globl _start
	.type main, @function

	_start:
		xor rbp,rbp /* recommended by the AMD64 ABI (probably optional) */

		pop rdi /* argc */
		mov rsi,rsp /* argv */
		and rsp,-16 /* zero the last 4 bits of rsp, aligning it to 16 bytes */
		call main

		mov rax,SYS_exit
		syscall
		ret

	/* syscalls */
	.globl syscall1, syscall2, syscall3

	syscall1:
		mov rax,rdi
		mov rdi,rsi
		ret

	syscall2:
		mov rax,rdi
		mov rdi,rsi
		mov rsi,rdx
		syscall
		ret

	syscall3:
		mov rax,rdi /* syscall number */
		mov rdi,rsi /* arg1 */
		mov rsi,rdx /* arg2 */
		mov rdx,rcx /* arg3 */
		syscall
		ret

#undef STDLOLI_ASM
