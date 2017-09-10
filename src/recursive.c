/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:31:21 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:31:35 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursive(t_file *f, t_options o)
{
	t_file *content;

	while (f != NULL)
	{
		if (S_ISDIR(f->statbuf.st_mode)
			&& !(o.all == false && f->name[0] == '.')
			&& ft_strcmp(".", f->name) != 0
			&& ft_strcmp("..", f->name) != 0)
		{
			ft_putchar('\n');
			ft_putstr(f->path);
			ft_putstr(":\n");
			if ((content = open_and_get(f)) != NULL)
			{
				if ((content->stat_statue == ERROR)
					|| (o.all == false && content->next->next == NULL))
				{
					display_file(content, o, false);
				}
				else
					display_file(content, o, true);
			}
		}
		f = f->next;
	}
}
