#include <stdloli.h>
#include <lolio.h>
#include <string.h>

int main() {
	char buf[32] = {0};

	itoa(10, 0x7FFFFFFF, buf, 0, 0);
	prln(buf);

	sprintf(buf, "%08X", 0xCAFE);
	prln(buf);

	sprintf(buf, "%x", 0xBADD);
	prln(buf);

	sprintf(buf, "%8x", 0xcafe);
	prln(buf);

	sprintf(buf, "%d", 12345);
	prln(buf);

	sprintf(buf, "%d", 0xFFFFFF00);
	prln(buf);

	sprintf(buf, "%u", 0xFFFFFF00);
	prln(buf);

	sprintf(buf, "%l", 12345678912345);
	prln(buf);

	return 0;
}
