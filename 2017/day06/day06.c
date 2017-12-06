#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

vector_generic(state, int *);

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
	struct state *st = state_init();
	int inf_at = 0, done = 0;
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
		state_insert(st, memdup(arr, sizeof(int) * size));
		for (i = 0; i < st->len - 1 && !inf_at; i++) /* detect infinite loop in state */
			if (!memcmp(st->arr[i], arr, sizeof(int) * size))
				printf("Part 1: %d cycles\n", (inf_at = st->len));
		if (inf_at && st->len != inf_at) /* wait 1 cycle before measuring infinite loop */
			if (!memcmp(st->arr[inf_at - 1], arr, sizeof(int) * size))
					printf("Part 2: %d more cycles\n", st->len - inf_at), done = !done;
	}
	free(arr);
	for (i = 0; i < st->len; i++)
		free((!st->arr[i]) ? NULL : st->arr[i]);
	state_free(st);
	token_free(bank);
	free(in);
	return 0;
}
