#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	struct split *tk = tokenize(in, "\n");
	unsigned i;
	for (i = 0; i < tk->num; i++)
		fprintf(stdout, "%s\n", tk->token[i]);
	token_free(tk);
	free(in);
	return 0;
}
