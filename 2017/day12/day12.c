#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

struct prog {
	int pid, visit;
	struct conn *cn;
};

vector_generic(ls, struct prog);
vector_generic(conn, int);

struct prog *fetch(struct ls *list, int pid)
{
	/* create new if none exists */
	unsigned i;
	for (i = 0; i < list->len; i++)
		if (list->arr[i].pid == pid)
			return &list->arr[i];
	return ls_insert(list, (struct prog) { pid, 0, conn_init() });
}

void reset_list(struct ls *list)
{
	/* resets visited status */
	unsigned i;
	for (i = 0; i < list->len; i++)
		list->arr[i].visit = 0;
}

unsigned count_deps(struct ls *list, int pid)
{
	/* traverse undirected graph */
	unsigned i, sum = 0;
	struct prog *p = fetch(list, pid);
	if (p->visit)
		return 0;
	for (i = 0; i < p->cn->len; i++)
	{
		p->visit = 1;
		sum += count_deps(list, p->cn->arr[i]);
	}
	return sum + 1;
}

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	struct ls *list = ls_init();
	struct split *line = tokenize(in, "\n");
	unsigned i, j, groups = 0;
	for (i = 0; i < line->num; i++) /* gather state */
	{
		struct split *word = tokenize(line->token[i], "<->, ");
		struct prog *p = fetch(list, atoi(*word->token));
		for (j = 1; j < word->num; j++)
			conn_insert(p->cn, atoi(word->token[j]));
		token_free(word);
	}
	printf("Part 1: %d programs\n", count_deps(list, 0));
	reset_list(list); /* undo visited flags */
	for (i = 0; i < list->len; i++)
		if (!list->arr[i].visit)
			groups += !!count_deps(list, list->arr[i].pid);
	printf("Part 2: %d groups\n", groups);
	for (i = 0; i < list->len; i++)
		conn_free(list->arr[i].cn);
	ls_free(list);
	token_free(line);
	free(in);
	return 0;
}
