#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 1, Part 2
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

struct point {
	int x;
	int y;
	enum { NORTH, EAST, SOUTH, WEST } dir;
	struct point *next;
};

struct list {
	struct point *head;
	unsigned depth;
};

/* blocks, not shortest distance */
#define distance(a, b) abs(abs((b).x - (a).x) + abs((b).y - (a).y))
#define is_equal(a, b) (((b).x == (a).x) && ((b).y == (a).y))

void list_insert(struct list *ls, struct point *pt)
{
	struct point *node = malloc(sizeof(struct point));
	*node = *pt; /* struct copy */
	node->next = ls->head;
	ls->head = node;
	ls->depth++;
}

void list_free(struct list *ls)
{
	while (ls->head != NULL)
	{
		struct point *node = ls->head;
		ls->head = node->next;
		free(node);
		ls->depth--;
	}
}

int list_search(struct list *ls, struct point *pt)
{
	unsigned i, found = 0;
	if (ls->head != NULL)
	{
		struct point **arr = malloc(sizeof(struct point *) * ls->depth);
		struct point *node = ls->head;
		for (i = 0; i < ls->depth; i++) /* unroll */
			arr[i] = node, node = node->next;
		for (i = ls->depth - 1; i > 0 && !found; --i)
			if (is_equal(*arr[i], *pt))
				found = !found;
		free(arr);
	}
	return found;
}

int main(void)
{
	char *ins = get_filebuffer(DAY(01));
/*	char *ins = get_filebuffer("input/poop.txt"); */
	struct list prev = { 0 };
	struct point orig = { 0 }, pt = { 0 }, act = { 0 };
	unsigned passed = 0;
	char *tok = strtok(ins, " ,");
	while (tok != NULL)
	{
		char rot;
		int dist;
		sscanf(tok, "%c%d", &rot, &dist);
		switch (rot)
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
		if (!passed && list_search(&prev, &pt))
			act = pt, passed = !passed; /* passed first duplicate coord */
		list_insert(&prev, &pt);
		tok = strtok(NULL, " ,");
	}
	printf("Coords: X: %d Y: %d Blocks: %d\n", pt.x, pt.y, distance(orig, pt));
	printf("Actual: X: %d Y: %d Blocks away: %d\n", act.x, act.y, distance(pt, act));
	list_free(&prev);
	free(ins);
	return 0;
}
