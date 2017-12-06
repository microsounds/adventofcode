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

/* generic vector container */
#define vector_generic(name, T) \
	struct name { T *arr; unsigned len, size; }; \
	struct name *name##_init(void) { \
		struct name *out = calloc(1, sizeof(struct name)); \
		out->size = 128; \
		out->arr = malloc(sizeof(T) * out->size); \
		return out; \
	} \
	void name##_insert(struct name *self, T insert) { \
		if (self->len == self->size) { \
			self->size *= 1.25f; \
			self->arr = realloc(self->arr, sizeof(T) * self->size); \
		} \
		self->arr[self->len++] = insert; \
	} \
	void name##_free(struct name *self) { \
		free((!self->arr) ? NULL : self->arr); \
		free((!self) ? NULL : self); \
	} \


#endif
