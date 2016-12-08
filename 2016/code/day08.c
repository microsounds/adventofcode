#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 8, Parts 1 & 2
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

#define WIDTH 50
#define HEIGHT 6
enum rotate { ROW, COLUMN };

void fill_rect(char **arr, unsigned x, unsigned y)
{
	/* fill rect from top left */
	unsigned i, j;
	for (i = 0; i < y; i++)
		for (j = 0; j < x; j++)
			arr[i][j] = 1;
}

void rotate_by(char **arr, enum rotate opt, int n, unsigned iters)
{
	/* shift row n 1 right
	 * shift column n 1 down
	 * wrap overflow characters
	 */
	unsigned i, j;
	for (i = 0; i < iters; i++)
	{
		if (opt == ROW)
		{
			char next = arr[n][WIDTH - 1];
			for (j = 0; j < WIDTH; j++)
			{
				char prev = arr[n][j];
				arr[n][j] = next;
				next = prev;
			}
		}
		else /* COLUMN */
		{
			char next = arr[HEIGHT - 1][n];
			for (j = 0; j < HEIGHT; j++)
			{
				char prev = arr[j][n];
				arr[j][n] = next;
				next = prev;
			}
		}
	}
}

int count_lit(char **arr)
{
	unsigned i, j, lit = 0;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (arr[i][j]) lit++;
			printf("%c", (arr[i][j]) ? '#' : '.');
			if (j == WIDTH - 1)
				printf("%c", '\n');
		}
	}
	return lit;
}

int main(void)
{
	char *ins = get_filebuffer(DAY(08));
	unsigned i, lines = 0;
	char **lcd = (char **) calloc(HEIGHT, sizeof(char *));
	for (i = 0; i < HEIGHT; i++)
		lcd[i] = (char *) calloc(WIDTH, sizeof(char));
	for (i = 0; ins[i]; i++)
		if (ins[i] == '\n') lines++;
	char **cmd = (char **) malloc(sizeof(char *) * lines);
	char *tok = strtok(ins, "\n");
	for (i = 0; tok != NULL; tok = strtok(NULL, "\n"))
		cmd[i++] = tok;
	for (i = 0; i < lines; i++) /* don't tokenize */
	{
		unsigned x, y, iters;
		if (strstr(cmd[i], "rect"))
		{
			sscanf(&cmd[i][5], "%dx%d", &x, &y);
			fill_rect(lcd, x, y);
		}
		else /* rotate */
		{
			if (strstr(cmd[i], "row"))
			{
				sscanf(&cmd[i][13], "%d by %d", &y, &iters);
				rotate_by(lcd, ROW, y, iters);
			}
			else /* column */
			{
				sscanf(&cmd[i][16], "%d by %d", &x, &iters);
				rotate_by(lcd, COLUMN, x, iters);
			}
		}
	}
	unsigned lit = count_lit(lcd);
	printf("%d pixels lit.\n", lit);
	for (i = 0; i < HEIGHT; i++)
		free(lcd[i]);
	free(lcd);
	free(cmd);
	free(ins);
	return 0;
}
