#pragma once

#include <lolint.h>

/* various types mostly used internally in the lib */

typedef intptr_t	fd_t;		/* file descriptor */
typedef uintptr_t	dev_t; 		/* device id */
typedef uintptr_t	ino_t; 		/* inode number */
typedef uint32_t	mode_t; 	/* file attributes bitmask */
typedef intptr_t	nlink_t; 	/* file link count */
typedef uint32_t	uid_t; 		/* user id */
typedef uint32_t	gid_t;		/* group id */
typedef intptr_t	off_t;		/* file size or offset */
typedef uintptr_t 	blksize_t;	/* block size */
typedef uintptr_t	blkcnt_t;	/* block count */
typedef intptr_t 	time_t;		/* seconds since epoch */
