#include "ft_ls.h"

int 		path_cmp(t_file *a, t_file *b)
{
	return (ft_strcmp (a->path, b->path));
}

int 		time_cmp(t_file *a, t_file *b)
{
	return (a->statbuf.st_mtime < b->statbuf.st_mtime);
}

static void	swap(t_file **a, t_file **b)
{
	t_file	tmp;

	tmp.path = (*a)->path;
	tmp.name = (*a)->name;
	tmp.statbuf = (*a)->statbuf;
	(*a)->path = (*b)->path;
	(*a)->statbuf = (*b)->statbuf;
	(*a)->name = (*b)->name;
	(*b)->path = tmp.path;
	(*b)->statbuf = tmp.statbuf;
	(*b)->name = tmp.name;
}

void		sort(t_file **list, int (*cmp)(t_file *f1, t_file *f2))
{
	t_file	*a;
	t_file	*b;

	a = *list;
	while (a)
	{
		b = a->next;
		while (b)
		{
			if (cmp(a, b) > 0)
			{
				swap(&a, &b);
			}
			b = b->next;
		}
		a = a->next;
	}
}

void	reverse_sort(t_file **file)
{
	t_file	*p_file;
	t_file	*q;
	t_file	*r;

	p_file = *file;
	q = NULL;
	while (p_file != NULL)
	{
		r = q;
		q = p_file;
		p_file = p_file->next;
		q->next = r;
	}
	*file = q;
}