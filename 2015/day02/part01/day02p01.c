#include <stdio.h>

/* Day 2: I Was Told There Would Be No Math */
/* Part 1 */
/* determine total sq. feet of wrapping paper based on:
 * <!> total surface area of the box
 * <!> slack length of the smallest area
 */

int min(int a, int b, int c)
{
	/* return smallest of 3 integers */
	int min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return min;
}

unsigned surface_area(int l, int w, int h)
{
	unsigned footage = 0;
	footage += 2 * l * w; /* length * width squared */
	footage += 2 * w * h; /* width * height squared */
	footage += 2 * h * l; /* height * length squared */

	/* add slack length (smallest area) */
	footage += min(l*w, w*h, h*l);
	return footage;
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
		total += surface_area(l, w, h);
	}
	printf("%u\n", total);
	fclose(file);
	return 0;
}
