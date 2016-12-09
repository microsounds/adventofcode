#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 4, Parts 1 and 2
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

struct freq {
	int count;
	char ch;
};

int sort_freq(const void *a, const void *b)
{
	return (*(struct freq *)b).count - (*(struct freq *)a).count;
}

int main(void)
{
	char *ins = get_filebuffer(DAY(04));
	unsigned i, j, lines = 0;
	for (i = 0; ins[i]; i++)
		if (ins[i] == '\n') lines++;
	char **arr = (char **) malloc(sizeof(char *) * lines);
	char *tok = strtok(ins, "\n");
	for (i = 0; tok != NULL; tok = strtok(NULL, "\n"))
		arr[i++] = tok;
	unsigned sum = 0;
	for (i = 0; i < lines; i++)
	{
		char *enc = strtok(arr[i], "[]");
		char *chk = strtok(NULL, "[]");
		struct freq lut[26] = { { 0 } };
		for (j = 0; j < 26; j++) /* lookup table */
			lut[j].ch = j + 'a';
		for (j = 0; enc[j]; j++)
			if (enc[j] >= '0' && enc[j] <= '9') break;
		unsigned sector_id = atoi(&enc[j]); /* sector id */
		enc[j - 1] = '\0'; /* hide sector id */
		for (j = 0; enc[j]; j++) /* count freq */
			if (enc[j] >= 'a' && enc[j] <= 'z')
				lut[enc[j] - 'a'].count++;
		qsort(lut, 26, sizeof(struct freq), sort_freq);
		unsigned valid = 1;
		for (j = 0; chk[j]; j++)
			if (chk[j] != lut[j].ch) /* checksum */
				valid = 0;
		if (valid)
		{
			sum += sector_id;
			for (j = 0; enc[j]; j++)
			{
				if (enc[j] == '-') /* cipher shift */
					enc[j] = ' ';
				else if (enc[j] >= 'a' && enc[j] <= 'z')
					enc[j] = (((enc[j] - 'a') + sector_id) % 26) + 'a';
			}
			if (strstr(enc, "northpole"))
				printf("#%d: Sector ID: %d '%s'\n", i + 1, sector_id, enc);
		}
	}
	printf("Sum of Sector IDs: %d\n", sum);
	free(arr);
	free(ins);
	return 0;
}
