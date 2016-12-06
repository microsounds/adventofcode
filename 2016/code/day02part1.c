#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 2, Part 1
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

/* bounds check */
#define clamp(n) ((n) > 2) ? 2 : ((n) < 0) ? 0 : n

int main(void)
{
	char *ins = get_filebuffer(DAY(02));
	int pad[3][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};
	struct {
		int y;
		int x;
	} pos = { 1, 1 }; /* 5 */
	char *tok = strtok(ins, "\n");
	while (tok != NULL)
	{
		unsigned len = strlen(tok);
		unsigned i;
		for (i = 0; i < len; i++)
		{
			switch (tok[i])
			{
				case 'R': pos.x++; pos.x = clamp(pos.x); break;
				case 'D': pos.y++; pos.y = clamp(pos.y); break;
				case 'L': pos.x--; pos.x = clamp(pos.x); break;
				case 'U': pos.y--; pos.y = clamp(pos.y); break;
			}
		}
		printf("%d", pad[pos.y][pos.x]);
		tok = strtok(NULL, "\n");
	}
	putchar('\n');
	free(ins);
	return 0;
}
