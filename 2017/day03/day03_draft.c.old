#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 10000
#define INPUT 325489

void debug(const char *grid, const int size)
{
	unsigned i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			if (grid[(size * i) + j])
				printf("%d\t", grid[(size * i) + j]);
		putchar('\n');
	}
	putchar('\n');
}

int main(void)
{
	int ctr = (SIZE / 2) - 1;
	/* flat 2D array */
	unsigned *grid = calloc(SIZE * SIZE, sizeof(unsigned));
	unsigned n = 2;
	int x = ctr, y = ctr, dist = 1;
	grid[(SIZE * y) + x] = 1;
	while (n < INPUT)
	{
		unsigned i;
		for (i = 0; i < dist; i++) /* right */
		{
			x++;
			n = 0;
			n += grid[(SIZE * (y - 1)) + (x - 1)];
			n += grid[(SIZE * (y - 1)) + x];
			n += grid[(SIZE * (y - 1)) + (x + 1)];
			n += grid[(SIZE * y) + (x - 1)];
			n += grid[(SIZE * y) + x];
			n += grid[(SIZE * y) + (x + 1)];
			n += grid[(SIZE * (y + 1)) + (x - 1)];
			n += grid[(SIZE * (y + 1)) + x];
			n += grid[(SIZE * (y + 1)) + (x + 1)];
			printf("%d\n", n);
			grid[(SIZE * y) + x] = n;
		}
		for (i = 0; i < dist; i++) /* up */
		{
			y--;
			n = 0;
			n += grid[(SIZE * (y - 1)) + (x - 1)];
			n += grid[(SIZE * (y - 1)) + x];
			n += grid[(SIZE * (y - 1)) + (x + 1)];
			n += grid[(SIZE * y) + (x - 1)];
			n += grid[(SIZE * y) + x];
			n += grid[(SIZE * y) + (x + 1)];
			n += grid[(SIZE * (y + 1)) + (x - 1)];
			n += grid[(SIZE * (y + 1)) + x];
			n += grid[(SIZE * (y + 1)) + (x + 1)];
			printf("%d\n", n);
			grid[(SIZE * y) + x] = n;
		}
		dist++;
		for (i = 0; i < dist; i++) /* left */
		{
			x--;
			n = 0;
			n += grid[(SIZE * (y - 1)) + (x - 1)];
			n += grid[(SIZE * (y - 1)) + x];
			n += grid[(SIZE * (y - 1)) + (x + 1)];
			n += grid[(SIZE * y) + (x - 1)];
			n += grid[(SIZE * y) + x];
			n += grid[(SIZE * y) + (x + 1)];
			n += grid[(SIZE * (y + 1)) + (x - 1)];
			n += grid[(SIZE * (y + 1)) + x];
			n += grid[(SIZE * (y + 1)) + (x + 1)];
			printf("%d\n", n);
			grid[(SIZE * y) + x] = n;
		}
		for (i = 0; i < dist; i++) /* down */
		{
			y++;
			n = 0;
			n += grid[(SIZE * (y - 1)) + (x - 1)];
			n += grid[(SIZE * (y - 1)) + x];
			n += grid[(SIZE * (y - 1)) + (x + 1)];
			n += grid[(SIZE * y) + (x - 1)];
			n += grid[(SIZE * y) + x];
			n += grid[(SIZE * y) + (x + 1)];
			n += grid[(SIZE * (y + 1)) + (x - 1)];
			n += grid[(SIZE * (y + 1)) + x];
			n += grid[(SIZE * (y + 1)) + (x + 1)];
			printf("%d\n", n);
			grid[(SIZE * y) + x] = n;
		}
		dist++;
	}

#if 0
	while (n < INPUT)
	{
		/* right up left down */
		/* every 2 directions, increase distance by 1 */
		unsigned i;
		for (i = 0; i < dist; i++) /* right */
		{
			grid[(SIZE * y) + ++x] = n++;
			if (n - 1 == 325489) printf("x %d y %d, c %d %d\n", x, y, ctr, ctr);
		}
		for (i = 0; i < dist; i++) /* up */
		{
			grid[(SIZE * --y) + x] = n++;
			if (n - 1 == 325489) printf("x %d y %d, c %d %d\n", x, y, ctr, ctr);
		}
		dist++;
		for (i = 0; i < dist; i++) /* left */
		{
			grid[(SIZE * y) + --x] = n++;
			if (n - 1 == 325489) printf("x %d y %d, c %d %d\n", x, y, ctr, ctr);
		}
		for (i = 0; i < dist; i++) /* down */
		{
			grid[(SIZE * ++y) + x] = n++;
			if (n - 1 == 325489) printf("x %d y %d, c %d %d\n", x, y, ctr, ctr);
		}
		dist++;
/*		debug(grid);*/
	}
#endif

}
