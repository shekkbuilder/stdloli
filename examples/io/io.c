#include <lolio.h>

int main() {
	// stdout
	fwrite(stdout, "Hello stdout from fwrite!\n", 26);
	fputs(stdout, "Hello stdout from fputs!\n");
	puts("Hello from puts!\n");
	prln("Hello from prln!");

	// stderr
	fwrite(stderr, "Hello stderr from fwrite!\n", 26);
	fputs(stderr, "Hello stderr from fputs!\n");

	// file operations
	prln("Creating & writing to file");
	fd_t f = fmake("test", o_wonly, 0666);
	if (f < 0) {
		prln("Failed to create file");
		return 1;
	}
	fputs(f, "Hello file!");
	fclose(f);

	prln("Reading from file");
	f = fopen("test", o_ronly);
	if (f < 0) {
		prln("Failed to open file");
		return 1;
	}
	char buf[16] = {0};
	fread(f, buf, 16);
	puts("Contents of the file: ");
	prln(buf);
	fclose(f);

	return 0;
}
