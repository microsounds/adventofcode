#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"
#define max(a, b) (((a) > (b)) ? (a) : (b))

/* 3D cartesian coordinates
 * against a hexagonal grid
 *
 *   +y
 *     \____/
 *     /\  /\
 *  __/__\/__\__ x+
 *    \  /\  /
 *     \/__\/
 *     /    \
 *    z+
 */

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	struct split *dir = tokenize(in, "\n, ");
	unsigned i;
	int x = 0, y = 0, z = 0, dist = 0;
	for (i = 0; i < dir->num; i++)
	{
		const char *t = dir->token[i];
		if (!strcmp("n", t))  { z--; y++; }
		if (!strcmp("nw", t)) { x--; y++; }
		if (!strcmp("nw", t)) { x--; y++; }
		if (!strcmp("ne", t)) { z--; x++; }
		if (!strcmp("s", t))  { z++; y--; }
		if (!strcmp("sw", t)) { z++; x--; }
		if (!strcmp("se", t)) { x++; y--; }
		if (dist < max(x, max(y, z)))
			dist = max(x, max(y, z));
	}
	printf("Part 1: %d steps\n", max(abs(x + y), z));
	printf("Part 2: %d steps\n", dist);
	token_free(dir);
	free(in);
	return 0;
}
