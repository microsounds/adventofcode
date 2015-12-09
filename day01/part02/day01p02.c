#include <stdio.h>

/* Day 1: Not Quite Lisp */
/* Part 2 */
/* determine file position of the first character
 * that enters the basement (floor -1)
 */

int get_floorno(FILE *fp)
{
	int up = 0;
	int down = 0;
	long pos = 0;
	char c;
	while ((c = fgetc(fp)) && !feof(fp))
	{
		if (c == '(')
			up++;
		else if (c == ')')
			down++;

		pos++; /* obtain file position */
		if ((up - down) == -1)
		{
			return pos;
		}
	}
	return up - down; /* failsafe */
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
