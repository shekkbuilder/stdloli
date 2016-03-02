#pragma once
#include <types.h>

/* contains information about a file */
typedef struct {
	dev_t		dev;
	ino_t		ino;
	nlink_t		nlink; /* hard links count */
	mode_t		mode;
	uid_t		uid;
	gid_t		gid;
	dev_t		rdev;
	off_t		size;
	blksize_t	blksize;
	blkcnt_t	blocks;
	time_t 		atime; /* access time */
	time_t		atime_nsec;
	time_t		mtime; /* modification time */
	time_t		mtime_nsec;
	time_t		ctime; /* status change time */
	time_t		ctime_nsec;
} stat_t;

int stat(const char* fname, stat_t* pstat);
int fstat(fd_t f, stat_t* pstat);
int lstat(const char* fname, stat_t* pstat);
