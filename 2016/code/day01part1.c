#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 1, Part 1
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

/* blocks, not shortest distance */
#define distance(a, b) abs(abs(b.x - a.x) + abs(b.y - a.y))

struct point {
	int x;
	int y;
	enum { NORTH, EAST, SOUTH, WEST } dir;
};

int main(void)
{
	char *ins = get_filebuffer(DAY(01));
	struct point orig = { 0 };
	struct point pt = { 0 };
	char *tok = strtok(ins, " ,");
	while (tok != NULL)
	{
		char dir;
		int dist;
		sscanf(tok, "%c%d", &dir, &dist);
		switch (dir)
		{
			case 'L': pt.dir = (pt.dir == NORTH) ? WEST : pt.dir - 1; break;
			case 'R': pt.dir = (pt.dir == WEST) ? NORTH : pt.dir + 1; break;
		}
		switch (pt.dir)
		{
			case NORTH: pt.y += dist; break;
			case EAST: pt.x += dist; break;
			case SOUTH: pt.y -= dist; break;
			case WEST: pt.x -= dist; break;
		}
		tok = strtok(NULL, " ,");
	}
	printf("Coords: X: %d Y: %d Blocks: %d\n", pt.x, pt.y, distance(orig, pt));
	free(ins);
	return 0;
}
