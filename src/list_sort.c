/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:44:53 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:45:08 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_lstswap(t_list **a, t_list **b)
{
	t_list tmp;

	tmp.content = (*a)->content;
	tmp.content_size = (*a)->content_size;
	(*a)->content = (*b)->content;
	(*a)->content_size = (*b)->content_size;
	(*b)->content = tmp.content;
	(*b)->content_size = tmp.content_size;
}

int			lst_alpha_cmp(t_list *a, t_list *b)
{
	return (ft_strcmp(a->content, b->content));
}

void		ft_lstsort(t_list **list, int (*cmp)(t_list *a, t_list *b))
{
	t_list *a;
	t_list *b;

	a = *list;
	while (a != NULL)
	{
		b = a->next;
		while (b != NULL)
		{
			if (cmp(a, b) > 0)
			{
				ft_lstswap(&a, &b);
			}
			b = b->next;
		}
		a = a->next;
	}
}
