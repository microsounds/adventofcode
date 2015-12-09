#include <stdio.h>

/* Day 3: Perfectly Spherical Houses in a Vacuum */
/* Part 2 */
/* determine how many houses were actually visited
 * aka how many houses received more than 0 presents
 * <!> keep track of 2 santas moving independently
 */

unsigned visited_houses(FILE *fp)
{
	unsigned map[500][500] = { {0} };
	unsigned x = 500 / 2; /* santa's coordinates */
	unsigned y = 500 / 2;
	unsigned a = 500 / 2; /* robo-santa's coordinates */
	unsigned b = 500 / 2;
	char c;
	unsigned turn = 0; /* 0 = santa, 1 = robo-santa */
	while ((c = fgetc(fp)) && !feof(fp))
	{
		if (turn) /* add 1 present to every house */
			map[x][y]++;
		else
			map[a][b]++;

		switch (c) /* traverse map */
		{
			case '^': (turn) ? y-- : b--; break; /*      y--      */
			case '<': (turn) ? x-- : a--; break; /*       ^       */
			case '>': (turn) ? x++ : a++; break; /* x-- < O > x++ */
			case 'v': (turn) ? y++ : b++; break; /*       v       */
			default: break;		  				 /*      y++      */
		}
		turn = !turn; /* switch turns */
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
