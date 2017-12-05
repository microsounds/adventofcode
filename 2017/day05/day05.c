#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"
#define static_size(p) (sizeof(p) / sizeof(*p))

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	struct split *line = tokenize(in, "\n");
	int *jmp[2];
	unsigned i, j;
	for (i = 0; i < static_size(jmp); i++)
		jmp[i] = malloc(sizeof(int) * line->num);
	for (i = 0; i < static_size(jmp); i++)
		for (j = 0; j < line->num; j++) /* atoi only once */
			jmp[i][j] = (!i) ? atoi(line->token[j]) : jmp[i - 1][j];
	for (i = 0; i < static_size(jmp); i++)
	{
		int steps = 0, ptr = 0;
		while (ptr > -1 && ptr < line->num)
		{
			int ins = jmp[i][ptr];
			jmp[i][ptr] = (!i) ? ins + 1 : (ins > 2) ? ins - 1 : ins + 1;
			ptr += ins;
			steps++;
		}
		fprintf(stdout, "Part %d: %d steps\n", i + 1, steps);
	}
	for (i = 0; i < static_size(jmp); i++)
		free((!jmp[i]) ? NULL : jmp[i]);
	token_free(line);
	free(in);
	return 0;
}
