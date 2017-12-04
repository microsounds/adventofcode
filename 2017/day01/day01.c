#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	/* part 1 */
	unsigned i, p1sum = 0, len = strlen(in);
	for (i = 1; i < len; i++)
	{
		/* cycle back to start */
		char next = (i == len - 1) ? in[0] : in[i];
		if (in[i - 1] == next)
			p1sum += in[i - 1] - '0';
	}
	/* part 2 */
	unsigned p2sum = 0;
	/* trailing newlines */
	char *p = in + len; while (*--p == '\n' && (len = p - in));
	for (i = 0; i < len; i++)
	{
		/* cycle halfway */
		char next = in[(i + (len / 2)) % len];
		if (in[i] == next)
			p2sum += in[i] - '0';
	}
	fprintf(stdout, "Part 1: %u\nPart 2: %u\n", p1sum, p2sum);
	free(in);
	return 0;
}
