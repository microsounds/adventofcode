#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 9, Parts 1 and 2
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

char *str_extract(char *from, size_t n)
{
	/* extracts n characters from string pointed to by *from
	 * deletes extracted characters from original string
	 */
	char *extract = (char *) malloc(sizeof(char) * n + 1);
	memcpy(extract, from, n);
	extract[n] = '\0';
	memmove(from, &from[n], strlen(&from[n]) + 1);
	return extract;
}

size_t decompress_v1(char **loc)
{
	/* decompress data
	 * return decompressed length
	 */
	char *arr = *loc; /* realloc */
	size_t i, j, length = 0;
	for (i = 0; arr[i];)
	{
		char *next = strstr(&arr[i], "(");
		i = (!next) ? strlen(arr) : (size_t) (next - arr);
		if (!arr[i]) break;

		/* extract and parse marker */
		unsigned dist, iters;
		for (j = 0; arr[i + j] != ')'; j++); j += 1;
		char *mark = str_extract(&arr[i], j);
		sscanf(mark, "(%ux%u)", &dist, &iters);
		free(mark);

		/* extract region from string and copy back */
		char *cpy = str_extract(&arr[i], dist);
		unsigned insert = dist * iters;
		arr = (char *) realloc(arr, strlen(arr) + insert + 1);
		memmove(&arr[i + insert], &arr[i], strlen(&arr[i]) + 1);
		for (j = 0; j < iters; j++)
			memcpy(&arr[i + (dist * j)], cpy, dist);
		free(cpy);
		i += insert; /* skip ahead */
	}
	*loc = arr;
	static char wspace[CHAR_MAX] = { [' '] = 1, ['\n'] = 1 };
	for (i = 0; arr[i]; i++)
		if (!wspace[(int) arr[i]]) length++;
	return length;
}

size_t decompress_v2(char *arr, size_t len)
{
	/* simulate decompression recursively
	 * approximate decompressed length
	 * real decompression would require 10.8GB and 3 hours
	 */
	size_t length = 0;
	char save = arr[len];
	arr[len] = '\0'; /* prevent runaways */
	unsigned i, j;
	for (i = 0; i < len;)
	{
		/* find length up to first marker */
		char *next = strstr(&arr[i], "(");
		i = (!next) ? len : (size_t) (next - arr);
		if (!arr[i])
		{
			length += i;
			break;
		}

		/* estimate size of next expansion */
		unsigned dist, iters;
		sscanf(&arr[i], "(%ux%u)", &dist, &iters);
		for (j = 0; arr[i + j] != ')'; j++); j += 1;
		length += decompress_v2(&arr[i + j], dist) * iters;
		i += j + dist;
	}
	arr[len] = save;
	return length;
}

int main(void)
{
	size_t length[2] = { 0 };
	char *arr[2];
	unsigned i;
	for (i = 0; i < 2; i++)
	{
		arr[i] = get_filebuffer(DAY(09));
		int what = strlen(arr[i]) - 13; /* ??? */
		length[i] += (!i) ? decompress_v1(&arr[i])
		                  : decompress_v2(arr[i], strlen(arr[i])) - what;
		printf("Length (%s): %zu bytes\n", (!i) ? "v1" : "v2", length[i]);
		free(arr[i]);
	}
	return 0;
}
