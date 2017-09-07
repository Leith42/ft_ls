#include "ft_ls.h"

int 		lexic_cmp(t_file *a, t_file *b)
{
	return (ft_strcmp (a->path, b->path));
}

int 		r_lexic_cmp(t_file *a, t_file *b)
{
	int cmp;

	if ((cmp = ft_strcmp(a->path, b->path)) > 0)
		return (-1);
	else if (cmp < 0)
		return (1);
	else
		return (0);
}

int 		time_cmp(t_file *a, t_file *b)
{
	if (a->statbuf.st_mtimespec.tv_sec != b->statbuf.st_mtimespec.tv_sec)
	{
		return (a->statbuf.st_mtimespec.tv_sec < b->statbuf.st_mtimespec.tv_sec);
	}
	else if (a->statbuf.st_mtimespec.tv_nsec != b->statbuf.st_mtimespec.tv_nsec)
	{
		return (a->statbuf.st_mtimespec.tv_nsec < b->statbuf.st_mtimespec.tv_nsec);
	}
	else
	{
		return (ft_strcmp(a->path, b->path));
	}
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

void		sort(t_file **list, int (*cmp)(t_file *a, t_file *b))
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

void FrontBackSplit(t_file* source, t_file **frontRef, t_file **backRef)
{
	t_file *fast;
	t_file *slow;
	if (source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

t_file *SortedMerge(t_file *a, t_file *b, int (*cmp)(t_file *a, t_file *b))
{
	t_file *result = NULL;

	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);
	if (cmp(a, b) <= 0)
	{
		result = a;
		result->next = SortedMerge(a->next, b, cmp);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next, cmp);
	}
	return(result);
}

void MergeSort(t_file **headRef, int (*cmp)(t_file *a, t_file *b))
{
	t_file *head = *headRef;
	t_file *a;
	t_file *b;

	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}
	FrontBackSplit(head, &a, &b);
	MergeSort(&a, cmp);
	MergeSort(&b, cmp);
	*headRef = SortedMerge(a, b, cmp);
}