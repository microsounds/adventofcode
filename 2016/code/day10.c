#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 10, Parts 1 and 2
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

#define BOTS 512
enum { LOW, HIGH };

struct bin {
	int idx;
	int store[10];
	struct {
		int addr;
		enum { BOT, OUT } mode;
	} send[2]; /* low, high */
};

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int main(void)
{
	char *ins = get_filebuffer(DAY(10));
	unsigned i, j, lines = 0;
	for (i = 0; ins[i]; i++)
		if (ins[i] == '\n') lines++;
	struct bin bot[BOTS] = { { 0 } };
	struct bin out[BOTS] = { { 0 } };
	char **arr = (char **) malloc(sizeof(char *) * lines);
	char *tok = strtok(ins, "\n");
	for (i = 0; tok != NULL; tok = strtok(NULL, "\n"))
		arr[i++] = tok;
	for (i = 0; i < lines; i++) /* program bots */
	{
		char *arg[20]; /* quick parse */
		tok = strtok(arr[i], " ");
		for (j = 0; tok != NULL; tok = strtok(NULL, " "))
			arg[j++] = tok;

		if (!strcmp(arg[0], "value")) /* value */
		{
			int n = atoi(arg[5]);
			bot[n].store[bot[n].idx++] = atoi(arg[1]);
		}
		else /* bot */
		{
			int n = atoi(arg[1]);
			for (j = 0; j < 2; j++)
			{
				int a = (j == LOW) ? 6 : 11;
				int m = (j == LOW) ? 5 : 10;
				bot[n].send[j].addr = atoi(arg[a]);
				bot[n].send[j].mode = (!strcmp(arg[m], "bot")) ? BOT : OUT;
			}
		}
	}
	int done = 0;
	while (!done) /* run commands */
	{
		done = 1;
		for (i = 0; i < BOTS; i++)
		{
			if (bot[i].idx >= 2)
			{
				done = 0; /* keep running */
				int low = min(bot[i].store[0], bot[i].store[1]);
				int high = max(bot[i].store[0], bot[i].store[1]);
				if (low == 17 && high == 61)
						printf("Bot %d has %d and %d.\n", i, low, high);
				for (j = 0; j < 2; j++) /* give */
				{
					int addr = bot[i].send[j].addr;
					int mode = bot[i].send[j].mode;
					struct bin *to = (mode == BOT) ? bot : out;
					to[addr].store[to[addr].idx++] = (j == LOW) ? low : high;
				}
				memset(&bot[i], 0, sizeof(struct bin)); /* wipe bot */
			}
		}
	}
	int sum = 1;
	for (i = 0; i < 3; i++)
		sum *= out[i].store[0];
	printf("Sum of outputs 0, 1, 2: %d\n", sum);
	free(ins);
	free(arr);
	return 0;
}
