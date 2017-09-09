/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:30:04 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:54:10 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_special_id_size(t_size *s, t_file *f)
{
	int min_len;
	int maj_len;

	min_len = (int)ft_nblen(MINOR(f->statbuf.st_rdev), BASE_DECIMAL);
	maj_len = (int)ft_nblen(MAJOR(f->statbuf.st_rdev), BASE_DECIMAL);
	if (s->min_pad < min_len)
	{
		s->min_pad = min_len;
	}
	if (s->maj_pad < maj_len)
	{
		s->maj_pad = maj_len;
	}
}

static void	get_usr_size(t_size *s, t_file *f)
{
	int				pw_name;
	struct passwd	*p;

	if ((p = getpwuid(f->statbuf.st_uid)) != NULL)
	{
		pw_name = (int)ft_strlen(p->pw_name);
		if (pw_name > s->user_pad)
			s->user_pad = pw_name;
	}
	else
	{
		pw_name = (int)ft_nblen(f->statbuf.st_uid, BASE_DECIMAL);
		if (pw_name > s->user_pad)
			s->user_pad = pw_name;
	}
}

static void	get_grp_size(t_size *s, t_file *f)
{
	int				gr_name;
	struct group	*g;

	if ((g = getgrgid(f->statbuf.st_gid)) != NULL)
	{
		gr_name = (int)ft_strlen(g->gr_name);
		if (gr_name > s->group_pad)
			s->group_pad = gr_name;
	}
	else
	{
		gr_name = (int)ft_nblen(f->statbuf.st_gid, BASE_DECIMAL);
		if (gr_name > s->group_pad)
			s->group_pad = gr_name;
	}
}

static void	get_current(t_file *f, t_size *s)
{
	int	link_pad;
	int size;

	link_pad = (int)ft_nblen(f->statbuf.st_nlink, BASE_DECIMAL);
	size = (int)ft_nblen(f->statbuf.st_size, BASE_DECIMAL);
	if (s->link_pad < link_pad)
	{
		s->link_pad = link_pad;
	}
	if (s->size_pad < size)
	{
		s->size_pad = size;
	}
	if (S_ISBLK(f->statbuf.st_mode) || S_ISCHR(f->statbuf.st_mode))
	{
		get_special_id_size(s, f);
	}
	get_grp_size(s, f);
	get_usr_size(s, f);
	s->total += f->statbuf.st_blocks;
}

t_size		get_size(t_file *f, t_options o)
{
	t_size size;

	ft_bzero(&size, sizeof(t_size));
	while (f != NULL)
	{
		if (!(o.all == false && f->name[0] == '.'))
		{
			get_current(f, &size);
		}
		f = f->next;
	}
	return (size);
}
