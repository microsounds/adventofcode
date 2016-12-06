#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 6, Parts 1 and 2
 */

char *get_filebuffer(const char *path)
{
	FILE *fp = fopen(path, "rb");
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *buf = (char *) malloc(sizeof(char) * len + 1);
	fread(buf, len, 1, fp);
	buf[len] = '\0';
	fclose(fp);
	return buf;
}

struct freq {
	int count;
	char ch;
};

int sort_freq(const void *a, const void *b)
{
	struct freq *x = (struct freq *)a;
	struct freq *y = (struct freq *)b;
	return x->count - y->count;
}

int main(void)
{
	char *ins = get_filebuffer(DAY(06));
	char arr[8][1024] = { { 0 } };
	unsigned i, j, idx = 0;
	char *tok = strtok(ins, "\n");
	while (tok != NULL)
	{
		for (i = 0; i < 8; i++)
			arr[i][idx] = tok[i];
		idx++;
		tok = strtok(NULL, "\n");
	}
	idx = 0;
	char msg[2][16] = { { 0 } };
	for (i = 0; i < 8; i++)
	{
		struct freq rep[26] = { { 0 } }; /* lookup table */
		for (j = 0; j < 26; j++)
			rep[j].ch = 'a' + j;
		for (j = 0; arr[i][j]; j++)
			rep[arr[i][j] - 'a'].count++;
		qsort(rep, 26, sizeof(struct freq), sort_freq);
		msg[0][idx] = rep[25].ch; /* most common */
		msg[1][idx++] = rep[0].ch; /* least common */
	}
	for (i = 0; i < 2; i++)
		printf("Part %d Message: %s\n", i + 1, msg[i]);
	free(ins);
	return 0;
}
