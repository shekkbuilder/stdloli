#include <lolio.h>
#include <stat.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fputs(stderr, "Usage: stat /path/to/file\n");
		return 1;
	}

	stat_t s = {0};
	if (lstat(argv[1], &s) < 0) {
		fputs(stderr, "Failed to stat file\n");
		return 1;
	}

	char buf[2048] = {0};
	sprintf(
		buf,
		"Device: %lu Inode: %lu\n"
		"Access: %o\n"
		"Hard Links: %ld\n"
		"User Id: %u Group Id: %u\n"
		"Special Device Id: %lu\n"
		"Size: %ld Block Size: %lu Blocks: %lu\n"
		"Access: %ld.%ld\n"
		"Modify: %ld.%ld\n"
		"Change: %ld.%ld\n", 
		s.dev, s.ino, s.mode, s.nlink, s.uid, s.gid, 
		s.rdev, s.size, s.blksize, s.blocks, 
		s.atime, s.atime_nsec, s.mtime, s.mtime_nsec, s.ctime, s.ctime_nsec
	);

	prln(buf);

	return 0;
}
