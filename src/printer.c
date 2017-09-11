/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:33:05 by aazri             #+#    #+#             */
/*   Updated: 2017/09/11 13:17:09 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define SIX_MONTHS 15778800

void	print_date(time_t date)
{
	char	*long_format;
	char	*str;
	char	*year;
	time_t	current_time;

	long_format = ctime(&date);
	if ((current_time = time(NULL)) == ERROR)
		exit(EXIT_FAILURE);
	if (current_time - date > SIX_MONTHS)
	{
		if ((year = ft_strsub(long_format, 20, 4)) == NULL
			|| (str = ft_strsub(long_format, 4, 6)) == NULL)
			exit(EXIT_FAILURE);
		ft_printf("%s  %s ", str, year);
		free(year);
	}
	else
	{
		if ((str = ft_strsub(long_format, 4, 12)) == NULL)
			exit(EXIT_FAILURE);
		ft_printf("%s ", str);
	}
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
