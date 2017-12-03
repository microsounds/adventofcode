#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define INPUT 325489

void debug(unsigned *grid, unsigned size)
{
	unsigned i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			printf("%d\t", grid[(size * i) + j]);
		putchar('\n');
	}
	putchar('\n');
}

int main(void)
{
	/* spiral array
	 * right up left down
	 * every 2 directions, increase distance by 1
	 */
	const unsigned SZ = sqrt(INPUT);
	unsigned ctr = SZ / 2;
	unsigned done = 0;

	/* part 1 - dry run only */
	unsigned n = 2;
	unsigned x = ctr, y = ctr, dist = 0, dir = 0;
	while (!done)
	{
		unsigned i;
		dist += !(dir & 1); /* distrance walked */
		for (i = 0; i < dist && !done; i++, n++)
		{
			switch (dir & 3) {
				case 0: x++; break; /* right */
				case 1: y--; break; /* up */
				case 2: x--; break; /* left */
				case 3: y++; break; /* down */
			}
			if (n == INPUT && (done = !done))
				printf("Part 1: %d steps\n", abs(x - ctr) + abs(y - ctr));
		}
		dir = (dir + 1) & 3;
	}
	/* part 2 -- simulate flat 2D array */
	unsigned *grid = calloc(SZ * SZ, sizeof(unsigned));
	grid[(SZ * ctr) + ctr] = 1; /* prime */
	done = 0; /* reset */
	x = ctr, y = ctr, dist = 0, dir = 0;
	while (!done)
	{
		unsigned i, j, k;
		dist += !(dir & 1); /* distrance walked */
		for (i = 0; i < dist && !done; i++)
		{
			switch (dir & 3) {
				case 0: x++; break; /* right */
				case 1: y--; break; /* up */
				case 2: x--; break; /* left */
				case 3: y++; break; /* down */
			}
			unsigned sum = 0;
			for (j = y - 1; j <= y + 1; j++)
				for (k = x - 1; k <= x + 1; k++)
					if (max(j, k) < SZ) /* bounds check */
						sum += grid[(SZ * j) + k];
			grid[(SZ * y) + x] = sum;
			if (sum > INPUT && (done = !done))
				printf("Part 2: %d\n", sum);
		}
		dir = (dir + 1) & 3;
	}
	free(grid);
	return 0;
}
