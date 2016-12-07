#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAY(n) "input/day" #n ".txt"

/* Advent of Code 2016
 * Solution for Day 7, Parts 1 and 2
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

int tls_support(char *str)
{
	unsigned i, bracket = 0; /* bracket flag */
	unsigned tally[2] = { 0 }; /* outside, inside */
	char *tok = strtok(str, "[]");
	while (tok != NULL)
	{
		unsigned len = strlen(tok);
		for (i = 0; i < len - 3; i++)
			if (tok[i] == tok[i+3] && tok[i+1] == tok[i+2]) /* 'abba' */
				if (tok[i] != tok[i+1]) /* 'aaaa' */
					tally[bracket]++;
		bracket = !bracket; /* flip */
		tok = strtok(NULL, "[]");
	}
	return (tally[0] && !tally[1]);
}

int ssl_support(char *str)
{
	unsigned tally = 0, idx = 0, bracket = 0; /* bracket flag */
	char *arr[2][1024] = { { 0 } }; /* outside, inside */
	char *tok = strtok(str, "[]");
	while (tok != NULL)
	{
		arr[bracket][idx] = tok;
		if (bracket) idx++;
		bracket = !bracket; /* flip */
		tok = strtok(NULL, "[]");
	}
	unsigned i, j, k;
	for (i = 0; arr[0][i]; i++)
	{
		char *a = arr[0][i];
		unsigned len = strlen(a);
		for (j = 0; j < len - 2; j++)
		{
			if (a[j] == a[j+2] && a[j] != a[j+1]) /* 'aba' */
			{
				char b[4] = { a[j+1], a[j], a[j+1], '\0' }; /* 'bab' */
				for (k = 0; arr[1][k]; k++)
					if (strstr(arr[1][k], b)) tally++;
			}
		}
	}
	return !!tally;
}

int main(void)
{
	char *ins = get_filebuffer(DAY(07));
	char *const mode[2] = { "TLS", "SSL" };
	int (*exec[2])(char *) = { &tls_support, &ssl_support };
	unsigned i, j, lines = 0;
	unsigned tally[2] = { 0 };
	for (i = 0; ins[i]; i++)
		if (ins[i] == '\n') lines++;
	char **arr = (char **) malloc(sizeof(char *) * lines);
	char *tok = strtok(ins, "\n");
	for (i = 0; tok != NULL; tok = strtok(NULL, "\n"))
		arr[i++] = tok;
	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < 2; j++)
		{
			char *str = (char *) malloc(sizeof(char) * strlen(arr[i]) + 1);
			strcpy(str, arr[i]);
			tally[j] += exec[j](str);
			free(str);
		}
	}
	for (i = 0; i < 2; i++)
		printf("%d out of %d support %s\n", tally[i], lines, mode[i]);
	free(arr);
	free(ins);
	return 0;
}
