#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 3, Part 2
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

int valid_triangle(int *arr)
{
	if (arr[0] + arr[1] > arr[2] &&
	    arr[0] + arr[2] > arr[1] &&
	    arr[1] + arr[2] > arr[0])
		return 1;
	else
		return 0;
}

int main(void)
{
	char *ins = get_filebuffer(DAY(03));
	int sides[3][3] = { { 0 } };
	unsigned col = 0, row = 0;
	unsigned valid = 0;
	char *tok = strtok(ins, " \n");
	while (tok != NULL)
	{
		sscanf(tok, "%d", &sides[row++ % 3][col % 3]); /* vertical */
		if ((row % 3) == 2)
			col++;
		if (!(row % 3) && !(col % 3))
		{
			unsigned i; /* flatten array */
			for (i = 0; i < 3; i++)
			{
				int arr[3] = { sides[i][0], sides[i][1], sides[i][2] };
				if (valid_triangle(arr))
					valid++;
			}
		}
		tok = strtok(NULL, " \n");
	}
	printf("Valid triangles: %d\n", valid);
	free(ins);
	return 0;
}
