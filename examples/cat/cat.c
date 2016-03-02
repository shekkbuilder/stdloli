#include <lolio.h>

#ifndef cat_bufsize 
#define cat_bufsize 512
#endif

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fputs(stderr, "Usage: cat /path/to/file\n");
		return 1;
	}

	// TODO: implement use sendfile or splice
	fd_t f = fopen(argv[1], o_ronly);
	if (f < 0) {
		fputs(stderr, "Failed to open file\n");
		return 1;
	}

	char buf[cat_bufsize] = {0};
	for (int cb = 0; 
		 (cb = fread(f, buf, cat_bufsize)); 
		 fwrite(stdout, buf, cb));

	fclose(f);

	return 0;
}
