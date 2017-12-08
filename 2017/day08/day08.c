#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

struct reg {
	char *name;
	int val, lg;
};

vector_generic(vec, struct reg);

enum cond { WHAT, LT, GT, EQ, GE, LE, NE } condition(const char *tk)
{
	const struct { enum cond c; const char *s; } tbl[] = {
		{ LT, "<" }, { GT, ">" },
		{ EQ, "==" }, { GE, ">=" },
		{ LE, "<=" }, { NE, "!=" }
	};
	unsigned i;
	for (i = 0; i < sizeof(tbl) / sizeof(*tbl); i++)
		if (!strcmp(tk, tbl[i].s))
			return tbl[i].c;
	return WHAT;
}

struct reg *lookup(struct vec *sym, const char *name)
{
	/* look up symbol table */
	/* create register if it doesn't exist yet */
	unsigned i;
	for (i = 0; i < sym->len; i++)
		if (!strcmp(name, sym->arr[i].name))
			return &sym->arr[i];
	return vec_insert(sym, ((struct reg) { memdup(name, strlen(name)), 0 }));
}

int main(int argc, char **argv)
{
	char *in;
	if (!argv[1] || !(in = get_filebuffer(argv[1])))
		return puts("Input?"), 1;

	struct split *line = tokenize(in, "\n");
	struct vec *sym = vec_init();
	unsigned i;
	for (i = 0; i < line->num; i++)
	{
		struct split *tk = tokenize(line->token[i], " ");
		struct reg *p = lookup(sym, tk->token[0]);
		struct reg *q = lookup(sym, tk->token[4]);
		int n1 = atoi(tk->token[2]);
		int n2 = atoi(tk->token[6]);
		int inc = (!strcmp("inc", tk->token[1])) ? 1 : -1;
		switch (condition(tk->token[5])) {
			case LT: p->val += ((q->val < n2) ? n1 : 0) * inc; break;
			case GT: p->val += ((q->val > n2) ? n1 : 0) * inc; break;
			case EQ: p->val += ((q->val == n2) ? n1 : 0) * inc; break;
			case GE: p->val += ((q->val >= n2) ? n1 : 0) * inc; break;
			case LE: p->val += ((q->val <= n2) ? n1 : 0) * inc; break;
			case NE: p->val += ((q->val != n2) ? n1 : 0) * inc; break;
			case WHAT: /* DONT DO THIS */
			default: break;
		}
		p->lg = (p->val > p->lg) ? p->val : p->lg; /* set record */
		token_free(tk);
	}
	int lg_now = 0, lg_ever = 0;
	for (i = 0; i < sym->len; i++) /* find largest values */
	{
		if (sym->arr[i].val > lg_now)
			lg_now = sym->arr[i].val;
		if (sym->arr[i].lg > lg_ever)
			lg_ever = sym->arr[i].lg;
	}
	printf("Part 1: largest register now: %d\n", lg_now);
	printf("Part 2: largest register ever: %d\n", lg_ever);
	for (i = 0; i < sym->len; i++)
		free((!sym->arr[i].name) ? NULL : sym->arr[i].name);
	vec_free(sym);
	token_free(line);
	free(in);
	return 0;
}
