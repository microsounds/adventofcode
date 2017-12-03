#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_filebuffer(const char *path)
{
	FILE *fp;
	if (!(fp = (!strcmp(path, "-")) ? stdin : fopen(path, "r")))
		return NULL;
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *buf = (char *) malloc(sizeof(char) * len + 1);
	fread(buf, sizeof(char), len, fp);
	fclose(fp);
	return buf[len] = '\0', buf;
}

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return 1;
	unsigned i, sum = 0, len = strlen(in);
	/* trailing newlines */
	char *p = in + len; while (*--p == '\n' && (len = p - in));
	for (i = 0; i < len; i++)
	{
		/* cycle halfway */
		char next = in[(i + (len / 2)) % len];
		if (in[i] == next)
			sum += in[i] - '0';
	}
	fprintf(stdout, "%u\n", sum);
	free(in);
}
