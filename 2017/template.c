#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct membuf {
	unsigned char *mem;
	size_t len, size;
};

void *memdup(const void *src, size_t n)
{
	void *dest = malloc(sizeof(unsigned char) * n + 1);
	memcpy(dest, src, n);
	return ((unsigned char *)dest)[n] = '\0', dest;
}

struct membuf *membuf_init(void)
{
	struct membuf *out = calloc(1, sizeof(struct membuf));
	out->size = 1024; /* starting size */
	out->mem = malloc(sizeof(unsigned char) * out->size + 1);
	return out;
}

void membuf_free(struct membuf *self)
{
	free((!self->mem) ? NULL : self->mem);
	free((!self) ? NULL : self);
}

size_t membuf_fread(struct membuf *buf, size_t size, size_t nmemb, FILE *stream)
{
	if (buf->size < buf->len + (size * nmemb))
	{
		buf->size = (buf->size + (size * nmemb)) * 1.25f;
		buf->mem = realloc(buf->mem, buf->size + 1);
	}
	size_t items_written = fread(&buf->mem[buf->len], size, nmemb, stream);
	buf->len += items_written * size;
	return buf->mem[buf->len] = '\0', items_written;
}

char *get_filebuffer(const char *path)
{
	FILE *fp;
	if (!(fp = (!strcmp(path, "-")) ? stdin : fopen(path, "r")))
		return NULL;
	struct membuf *buf = membuf_init();
	while (membuf_fread(buf, sizeof(char), 1024, fp));
	if (fp != stdin) fclose(fp);
	char *out = NULL;
	if (buf->len)
		out = memdup(buf->mem, buf->len);
	membuf_free(buf);
	return out;
}

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return 1;
	unsigned i, sum = 0, len = strlen(in);
	char *ltok = strtok(in, "\n"), **lines = NULL;
	unsigned n = 0;
	while (ltok && ++n)
	{
		lines = realloc(lines, sizeof(char *) * n);
		lines[n - 1] = memdup(ltok, strlen(ltok));
		printf("%s\n", lines[n - 1]);
		ltok = strtok(NULL, "\n");
	}
	free(in);
}
