#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Day 10: Elves Look, Elves Say */
/* Part 1 */
/* iteratively generate a sequence based on the previous one
 * 1113222113 = three 1's, one 3, three 2's, two 1's, one 3
 * 1113222113 = 3113322113
 * return the length of the 40th iteration
 */

char *lookandsay(const char *str)
{
	const unsigned len = strlen(str);
	char *out = (char *) malloc(sizeof(char) * len * 2);
	unsigned i, focus, carriage;
	unsigned j = 0; /* output position */
	for (i = 0; i < len; j += 2)
	{
		/* char '5' - '0' (ascii val 30) = integer 5 */
		focus = *(str+i) - '0';
		carriage = i;
		while (1) /* advance carriage */
		{
			if (focus == *(str+carriage) - '0')
				carriage++;
			else
				break;
		}
		carriage -= i; /* carriage return */
		*(out+j) = carriage + '0';
		*(out+j+1) = focus + '0';
		i += carriage;
	}
	*(out+j) = '\0'; /* null terminate */
	free((char *)str);
	return out;
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
	char *str = (char *) malloc(sizeof(char) * 128);
	fscanf(file, "%s", str);
	unsigned iter = 0;
	const unsigned rounds = 40;
	while (iter < rounds)
	{
		/* lookandsay() free's input pointer and
		   returns a replacement for every iteration. */
		str = lookandsay(str);
		iter++;
	}
	printf("%d\n", strlen(str));

	free(str);
	fclose(file);
	return 0;
}
