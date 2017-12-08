#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

struct prog {
	char *name;
	unsigned weight;
	unsigned deps; /* directed graph */
	struct prog **sub; /* dependents */
	struct vec *desc; /* described by this node */
};

vector_generic(vec, char *);
vector_generic(ls, struct prog);

struct prog *node_search(struct ls *list, const char *name)
{
	unsigned i;
	for (i = 0; i < list->len; i++)
		if (!strcmp(name, list->arr[i].name))
			return &list->arr[i];
	return NULL; /* shouldn't be possible */
}

unsigned node_weight(struct prog *node)
{
	/* traverse node and
	 * gather weight of every subnode below it */
	if (!node)
		return 0;
	unsigned i, sum = 0;
	for (i = 0; i < node->deps; i++)
		sum += node_weight(node->sub[i]);
	return sum + node->weight;
}

unsigned *find_unique(unsigned *arr, unsigned len)
{
	/* return pointer to latest unique value */
	unsigned i, *uniq = NULL;
	if (len > 2) /* impossible */
		for (i = 1; i < len; i++)
			if (arr[i - 1] != arr[i])
				uniq = &arr[i - 1];
	return uniq;
}

void find_unbalanced(struct prog *node)
{
	if (node && node->deps)
	{
		unsigned i, *unbal = NULL;
		unsigned *curr = malloc(sizeof(unsigned) * node->deps);
		for (i = 0; i < node->deps; i++)
			curr[i] = node_weight(node->sub[i]);
		if ((unbal = find_unique(curr, node->deps)))
		{
			printf("'%s' has unbalanced subnodes:", node->name);
			for (i = 0; i < node->deps; i++)
				printf(" '%s': %d", node->sub[i]->name, curr[i]);
			putchar('\n');
			find_unbalanced(node->sub[unbal - curr]);
		}
		else
			printf("'%s' has weight %d\n", node->name, node->weight);
		free(curr);
	}
}

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	struct prog *root = NULL;
	struct split *line = tokenize(in, "\n");
	struct ls *list = ls_init();
	unsigned i, j, k;
	for (i = 0; i < line->num; i++) /* create flat list of nodes */
	{
		struct split *word = tokenize(line->token[i], " ->(),");
		struct prog node = {
			memdup(word->token[0], strlen(word->token[0])),
			atoi(word->token[1]),
			0,
			NULL,
			(word->num > 2) ? vec_init() : NULL
		};
		if (node.desc)
			for (j = 2; j < word->num; j++)
				vec_insert(node.desc, memdup(word->token[j], strlen(word->token[j])));
		ls_insert(list, node);
		token_free(word);
	}
	token_free(line);
	free(in);

	for (i = 0; i < list->len; i++) /* generate directed graph */
	{
		struct prog *p = &list->arr[i];
		if (p->desc)
		{
			p->deps = p->desc->len;
			p->sub = malloc(sizeof(struct prog *) * p->desc->len);
			for (j = 0; j < p->desc->len; j++)
				p->sub[j] = node_search(list, p->desc->arr[j]);
			for (j = 0; j < p->desc->len; j++)
				free((!p->desc->arr[j]) ? NULL : p->desc->arr[j]);
			vec_free(p->desc);
		}
	}
	for (i = 0; i < list->len; i++) /* find root */
	{
		int found = 1; /* root is not mentioned by any other node */
		for (j = 0; j < list->len && found; j++)
			if (list->arr[j].deps)
				for (k = 0; k < list->arr[j].deps; k++)
					if (!strcmp(list->arr[i].name, list->arr[j].sub[k]->name))
						found = 0;
		if (/* still */ found)
			root = &list->arr[i];
	}
	printf("Part 1: root is '%s'\n", root->name);
	printf("Part 2: AAAAAAAAAAAAAAAAAAAAAAAA\n");
	find_unbalanced(root);
	for (i = 0; i < list->len; i++)
	{
		free((!list->arr[i].name) ? NULL : list->arr[i].name);
		free((!list->arr[i].sub) ? NULL : list->arr[i].sub);
	}
	ls_free(list);

	return 0;
}
