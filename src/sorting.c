/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:23:41 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:28:04 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			reverse_sort(t_file **file)
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

static void		ft_frontbacksplit(t_file *source, t_file **frontref, \
	t_file **backref)
{
	t_file *fast;
	t_file *slow;

	if (source == NULL || source->next == NULL)
	{
		*frontref = source;
		*backref = NULL;
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
		*frontref = source;
		*backref = slow->next;
		slow->next = NULL;
	}
}

static t_file	*ft_sortedmerge(t_file *a, t_file *b, \
	int (*cmp)(t_file *a, t_file *b))
{
	t_file *result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (cmp(a, b) <= 0)
	{
		result = a;
		result->next = ft_sortedmerge(a->next, b, cmp);
	}
	else
	{
		result = b;
		result->next = ft_sortedmerge(a, b->next, cmp);
	}
	return (result);
}

void			ft_mergesort(t_file **headref, int (*cmp)(t_file *a, t_file *b))
{
	t_file *head;
	t_file *a;
	t_file *b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
	{
		return ;
	}
	ft_frontbacksplit(head, &a, &b);
	ft_mergesort(&a, cmp);
	ft_mergesort(&b, cmp);
	*headref = ft_sortedmerge(a, b, cmp);
}
