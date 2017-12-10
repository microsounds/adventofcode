#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"
#define static_size(p) (sizeof(p) / sizeof(*p))
#define SZ 256

void memrev(void *arr, unsigned n)
{
    unsigned i = n - 1, j = 0;
    unsigned char swp;
    while (i > j)
    {
        swp = ((unsigned char *)arr)[i];
        ((unsigned char *)arr)[i] = ((unsigned char *)arr)[j];
        ((unsigned char *)arr)[j] = swp;
        j++; i--;
    }
}

unsigned knothash_simple(char *in)
{
	struct split *input = tokenize(in, "\n, ");
	unsigned char *arr = malloc(sizeof(unsigned char) * SZ);
	unsigned i, j, out;
	unsigned idx = 0, skip = 0;
	for (i = 0; i < SZ; i++) arr[i] = i;
	for (i = 0; i < input->num; i++)
	{
		unsigned char len = atoi(input->token[i]) & 0xFF;
		if (len > 1) /* less than 2 has no effect */
		{
			unsigned char *sub = malloc(sizeof(unsigned char) * len);
			for (j = 0; j < len; j++) /* circular */
				sub[j] = arr[(idx + j) % SZ];
			memrev(sub, len);
			for (j = 0; j < len; j++)
				arr[(idx + j) % SZ] = sub[j];
			free(sub);
		}
		idx += len + skip++;
	}
	out = arr[0] * arr[1];
	free(arr);
	token_free(input);
	return out;
}

const char *knothash(char *in)
{
	const char hex[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};
	static char out[33] = { 0 };
	struct split *input = tokenize(in, "\n");
	char *msg = memdup(input->token[0], strlen(input->token[0]));
	unsigned length = strlen(msg);
	unsigned char salt[] = { 0x11, 0x1F, 0x49, 0x2F, 0x17, '\0' };
	msg = realloc(msg, length + static_size(salt));
	memcpy(msg + length, salt, static_size(salt)); /* add salt */
	length += static_size(salt) - 1;

	unsigned char dense[16] = { 0 };
	unsigned char *sparse = malloc(sizeof(unsigned char) * SZ);
	unsigned i, j, k;
	unsigned idx = 0, skip = 0;
	for (i = 0; i < SZ; i++) sparse[i] = i;
	for (i = 0; i < 64; i++) /* sparse hash -- 64 rounds */
	{
		for (j = 0; j < length; j++)
		{
			unsigned char len = msg[j] & 0xFF;
			if (len > 1) /* less than 2 has no effect */
			{
				unsigned char *sub = malloc(sizeof(unsigned char) * len);
				for (k = 0; k < len; k++) /* circular */
					sub[k] = sparse[(idx + k) % SZ];
				memrev(sub, len);
				for (k = 0; k < len; k++)
					sparse[(idx + k) % SZ] = sub[k];
				free(sub);
			}
			idx += len + skip++;
		}
	}
	for (i = 0; i < 16; i++) /* dense hash */
		for (j = 0; j < 16; j++)
			dense[i] ^= sparse[(i * 16) + j];
	for (i = 0; i < 16; i++) /* to hex */
	{
		out[(i * 2)] = hex[((dense[i] & 0xF0) >> 4)];
		out[(i * 2) + 1] = hex[dense[i] & 0xF];
	}
	free(msg);
	free(sparse);
	token_free(input);
	return out[32] = '\0', out;
}

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;
	char *p1in = in, *p2in = memdup(in, strlen(in));

	printf("Part 1: %u\n", knothash_simple(p1in));
	printf("Part 2: '%s'\n", knothash(p2in));

	free(p1in), free(p2in);
	return 0;
}
