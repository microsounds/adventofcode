#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Day 6: Probably a Fire Hazard */
/* Part 2 */
/* given a 1000x1000 array of lights,
 * adjust brightness according to specified inclusive ranges
 * return the total brightness of all the lights
 */

typedef enum { toggle, turn_on, turn_off } P_MODE;

typedef struct {
	unsigned x;
	unsigned y;
} POINT;

enum { SZ = 1000 }; /* array size constant */

unsigned get_iterations(FILE *fp, const char delimiter)
{
	long pos = ftell(fp);
	unsigned cases = 0;
	char c;
	while ((c = fgetc(fp)) && !feof(fp))
	{
		if (c == delimiter)
			cases++;
	}
	fseek(fp, pos, SEEK_SET);
	return cases;
}

unsigned get_linelength(FILE *fp, const char delimiter)
{
	long pos = ftell(fp);
	unsigned len = 0;
	while (fgetc(fp) != delimiter)
	{
		len++;
	}
	fseek(fp, pos, SEEK_SET);
	return len;
}

P_MODE detect_mode(char *str)
{
	/* parse command string */
	if (strstr(str, "turn"))
	{
		if (strstr(str, "on"))
			return turn_on;
		else
			return turn_off;
	}
	else
		return toggle;
}

void truncate_cmd(char *str, P_MODE mode)
{
	/* truncate command string */
	long pos;
	switch (mode)
	{
		case toggle:
			pos = 7; break;
		case turn_on:
			pos = 8; break;
		case turn_off:
			pos = 9; break;
		default: break;
	}
	memmove(str, str+pos, strlen(str));
}

void adjust_lights(P_MODE mode, int (*arr)[SZ][SZ], POINT from, POINT to)
{
	/* this may or may not work with all edge cases */
	unsigned i, j;
	for (i = from.x; i <= to.x; i++) /* x */
	{
		for (j = from.y; j <= to.y; j++) /* y */
		{
			switch (mode)
			{
				case toggle:
					(*arr)[i][j] += 2; break;
				case turn_on:
					(*arr)[i][j] += 1; break;
				case turn_off:
				{
					(*arr)[i][j] -= 1;
					if ((*arr)[i][j] < 0)
						(*arr)[i][j] = 0;
					break; /* brightness cannot be negative */
				}
				default: break;
			}
		}
	}
}

unsigned count_brightness(int (*arr)[SZ][SZ])
{
	unsigned brightness = 0;
	unsigned i, j;
	for (i = 0; i < SZ; i++)
	{
		for (j = 0; j < SZ; j++)
		{
			brightness += (*arr)[i][j];
		}
	}
	return brightness;
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
	int lights[SZ][SZ] = { { 0 } };
	int (*arr)[SZ][SZ] = &lights;
	unsigned cases = get_iterations(file, '\n');
	unsigned i = 0;
	while (i++ < cases)
	{
		unsigned len = get_linelength(file, '\n');
		char *str = (char *) malloc(sizeof(char) * len);
		fscanf(file, "%[^\n]\n", str);

		P_MODE mode = detect_mode(str);
		truncate_cmd(str, mode);

		POINT from, to;
		sscanf(str, "%u,%u %*s %u,%u", &from.x, &from.y, &to.x, &to.y);
		adjust_lights(mode, arr, from, to);
		free(str);
	}
	printf("%u\n", count_brightness(arr));
	fclose(file);
	return 0;
}
