#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	struct split *line = tokenize(in, "\n");
	unsigned i, j;
	for (i = 0; i < line->num; i++)
	{
		struct split *word = tokenize(line->token[i], " ");
		for (j = 0; j < word->num; j++)
			fprintf(stdout, "%s\n", word->token[j]);
		token_free(word);
	}
	token_free(line);
	free(in);
	return 0;
}
