#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	int i;
	struct split *bank = tokenize(in, " \t");
	int *arr = malloc(sizeof(int) * bank->num);
	for (i = 0; i < bank->num; i++)
		arr[i] = atoi(bank->token[i]);
	int size = bank->num;
	int **state = NULL;
	int iters = 0, inf_at = 0, done = 0;
	while (!done)
	{
		int lg = 0;
		for (i = size - 1; i >= 0; i--)
			if (arr[i] >= arr[lg]) /* break ties by prefering the lowest */
				lg = i;
		int spill = arr[lg]; /* distribute */
		arr[lg] = 0;
		while (spill--)
			arr[++lg % size]++;

		/* save previous iterations */
		state = realloc(state, sizeof(int *) * ++iters);
		state[iters - 1] = malloc(sizeof(int) * size);
		memcpy(state[iters - 1], arr, sizeof(int) * size);
		for (i = 0; i < iters - 1 && !inf_at; i++) /* detect infinite loop in state */
			if (!memcmp(state[i], arr, sizeof(int) * size))
				printf("Part 1: %d cycles\n", (inf_at = iters));
		if (inf_at && iters != inf_at) /* wait 1 cycle before measuring infinite loop */
			if (!memcmp(state[inf_at - 1], arr, sizeof(int) * size))
					printf("Part 2: %d more cycles\n", iters - inf_at), done = !done;
	}
	free(arr);
	token_free(bank);
	for (i = 0; i < iters; i++)
		free((!state[i]) ? NULL : state[i]);
	free(state);
	free(in);
	return 0;
}
