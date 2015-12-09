#include <stdio.h>

/* Day 3: Perfectly Spherical Houses in a Vacuum */
/* Part 1 */
/* determine how many houses were actually visited
 * aka how many houses received more than 0 presents
 */

unsigned visited_houses(FILE *fp)
{
	unsigned map[500][500] = { {0} };
	unsigned x = 500 / 2;
	unsigned y = 500 / 2;
	char c;
	while ((c = fgetc(fp)) && !feof(fp))
	{
		map[x][y]++; /* add 1 present to current house */
		switch (c) /* traverse map */
		{
			case '^': y--; break; /*      y--      */
			case '<': x--; break; /*       ^       */
			case '>': x++; break; /* x-- < O > x++ */
			case 'v': y++; break; /*       v       */
			default: break;       /*      y++      */
		}
	}
	unsigned i, j;
	unsigned visited = 0; /* check how many houses were visited */
	for (i = 0; i < 500; i++)
	{
		for (j = 0; j < 500; j++)
		{
			if (map[i][j])
			{
				visited++;
			}
		}
	}
	return visited;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}
	printf("%u\n", visited_houses(file));
	fclose(file);
	return 0;
}
