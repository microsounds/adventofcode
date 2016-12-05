#include <stdio.h>
#include <stdlib.h>

/* Day 2: I Was Told There Would Be No Math */
/* Part 2 */
/* determine total length of ribbon required based on:
 * <!> perimeters of the 2 shortest sides of the box
 * <!> cubic volume of the box for the bow
 */

int compar(const void *a, const void *b)
{
	int x = *(int *)a;
	int y = *(int *)b;
	return x - y;
}

unsigned ribbon_length(int l, int w, int h)
{
	unsigned length = 0;
	int arr[3] = {l, w, h}; /* obtain the 2 smallest values */
	qsort(&arr, 3, sizeof(int), compar);
	unsigned i = 0;
	while (i < 2)
	{
		length += arr[i] * 2; /* add perimeters of the 2 shortest sides */
		i++;
	}
	length += l * w * h; /* add cubic volume of box for bow */
	return length;
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
	unsigned l, w, h;
	unsigned total = 0;
	while (fscanf(file, "%ux%ux%u", &l, &w, &h) && !feof(file))
	{
		total += ribbon_length(l, w, h);
	}
	printf("%u\n", total);
	fclose(file);
	return 0;
}
