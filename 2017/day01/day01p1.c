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
	for (i = 1; i < len; i++)
	{
		/* cycle back to start */
		char next = (i == len - 1) ? in[0] : in[i];
		if (in[i - 1] == next)
			sum += in[i - 1] - '0';
	}
	fprintf(stdout, "%u\n", sum);
	free(in);
}
