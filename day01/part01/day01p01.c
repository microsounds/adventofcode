#include <stdio.h>

/* Day 1: Not Quite Lisp */
/* Part 1 */
/* determine floor number based on parentheses
 */
int get_floorno(FILE *fp)
{
	int up = 0;
	int down = 0;
	char c;
	while ((c = fgetc(fp)) && !feof(fp))
	{
		if (c == '(')
			up++;
		else if (c == ')')
			down++;
	}
	return up - down;
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
	printf("%d\n", get_floorno(file));
	fclose(file);
	return 0;
}
