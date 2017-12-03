#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

/* misc */

void *memdup(const void *src, size_t n)
{
	void *dest = malloc(sizeof(unsigned char) * n + 1);
	memcpy(dest, src, n);
	return ((unsigned char *)dest)[n] = '\0', dest;
}

/* membuf */

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

/* file input */

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

/* token split */

struct split *tokenize(char *str, const char *delims)
{
	struct split *tk = calloc(1, sizeof(struct split));
	char *tok = strtok(str, delims);
	while (tok && ++tk->num)
	{
		tk->token = realloc(tk->token, sizeof(char *) * tk->num);
		tk->token[tk->num - 1] = memdup(tok, strlen(tok));
		tok = strtok(NULL, delims);
	}
	return tk;
}

void token_free(struct split *self)
{
	unsigned i;
	for (i = 0; i < self->num; i++)
		free((!self->token[i]) ? NULL : self->token[i]);
	free((!self->token) ? NULL : self->token);
	free((!self) ? NULL : self);
}
