/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:33:05 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 19:05:55 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_date(time_t date)
{
	char *str;

	if ((str = ft_strsub(ctime(&date), 4, 12)) == NULL)
	{
		print_error("malloc");
		exit(EXIT_FAILURE);
	}
	ft_putstr(str);
	ft_putchar(' ');
	free(str);
}

void	print_special_id(dev_t id, int min_pad, int maj_pad)
{
	ft_printf("%*d, %*d ", maj_pad, MAJOR(id), min_pad, MINOR(id));
}

void	print_size(off_t size, t_size s)
{
	if (s.maj_pad > 0 || s.min_pad > 0)
	{
		if (s.maj_pad + s.min_pad + 2 > s.size_pad)
		{
			s.size_pad = s.maj_pad + s.min_pad + 2;
		}
	}
	ft_printf("%*ld ", s.size_pad, size);
}

void	print_grp(gid_t gid, int pad)
{
	struct group *g;

	if ((g = getgrgid(gid)) != NULL)
	{
		ft_printf("%-*s  ", pad, g->gr_name);
	}
	else
	{
		ft_printf("%-*d  ", pad, gid);
	}
}

void	print_not_found(t_list *f)
{
	ft_lstsort(&f, lst_alpha_cmp);
	while (f != NULL)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(f->content);
		ft_putstr(": No such file or directory\n");
		f = f->next;
	}
}
