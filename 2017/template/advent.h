#ifndef INPUT_H
#define INPUT_H

/* boilerplate library for retrieving inputs */

struct membuf {
	unsigned char *mem;
	size_t len, size;
};

struct split {
	char **token;
	unsigned num;
};

/* misc */
void *memdup(const void *, size_t);
/* membuf */
struct membuf *membuf_init(void);
void membuf_free(struct membuf *);
size_t membuf_fread(struct membuf *, size_t, size_t, FILE *);
/* file input */
char *get_filebuffer(const char *);
/* token split */
struct split *tokenize(char *, const char *);
void token_free(struct split *);

#endif
