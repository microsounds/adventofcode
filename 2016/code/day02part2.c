#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 2, Part 2
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

int main(void)
{
	char *ins = get_filebuffer(DAY(02));
	char pad[7][7] = {
		{   0,   0,   0,   0,   0,   0,   0 },
		{   0,   0,   0, '1',   0,   0,   0 },
		{   0,   0, '2', '3', '4',   0,   0 },
		{   0, '5', '6', '7', '8', '9',   0 },
		{   0,   0, 'A', 'B', 'C',   0,   0 },
		{   0,   0,   0, 'D',   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,   0 },
	};
	struct {
		int y;
		int x;
	} pos = { 3, 1 }; /* 5 */
	char *tok = strtok(ins, "\n");
	while (tok != NULL)
	{
		unsigned len = strlen(tok);
		unsigned i;
		for (i = 0; i < len; i++)
		{
			switch (tok[i])
			{
				case 'R': pos.x += (!!pad[pos.y][pos.x + 1]); break;
				case 'L': pos.x -= (!!pad[pos.y][pos.x - 1]); break;
				case 'D': pos.y += (!!pad[pos.y + 1][pos.x]); break;
				case 'U': pos.y -= (!!pad[pos.y - 1][pos.x]); break;
			}
		}
		printf("%c", pad[pos.y][pos.x]);
		tok = strtok(NULL, "\n");
	}
	putchar('\n');
	free(ins);
	return 0;
}
