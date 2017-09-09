/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:50:15 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:50:36 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	long_file_display(t_file *f, t_size s, t_options o)
{
	while (f != NULL)
	{
		if (f->stat_statue != ERROR && !(f->name[0] == '.' && o.all == false))
		{
			print_access(f);
			print_attribs(f);
			print_links(f->statbuf.st_nlink, s.link_pad);
			print_usr(f->statbuf.st_uid, s.user_pad);
			print_grp(f->statbuf.st_gid, s.group_pad);
			if (S_ISBLK(f->statbuf.st_mode) || S_ISCHR(f->statbuf.st_mode))
				print_special_id(f->statbuf.st_rdev, s.min_pad, s.maj_pad);
			else
				print_size(f->statbuf.st_size, s);
			print_date(f->statbuf.st_mtime);
			print_name(f, o);
		}
		f = f->next;
	}
}

void	simple_file_display(t_file *f, t_options o)
{
	while (f != NULL)
	{
		if (f->stat_statue != ERROR && !(o.all == false && f->name[0] == '.'))
		{
			print_name(f, o);
		}
		f = f->next;
	}
}

void	display_file(t_file *f, t_options o, bool print_total)
{
	t_size s;

	if (o.time_sort == true)
	{
		ft_mergesort(&f, time_cmp);
		if (o.reverse_sort == true)
			reverse_sort(&f);
	}
	else if (o.reverse_sort == true)
		ft_mergesort(&f, r_lexic_cmp);
	else
		ft_mergesort(&f, lexic_cmp);
	if (o.l_display == true)
	{
		s = get_size(f, o);
		if (print_total == true)
			ft_printf("total %d\n", s.total);
		long_file_display(f, s, o);
	}
	else
		simple_file_display(f, o);
	if (o.recursive == true)
		recursive(f, o);
	free_file(f);
}

void	handle_file(t_list *paths, t_options o)
{
	t_file *files;

	files = NULL;
	o.all = true;
	while (paths != NULL)
	{
		get_files(&files, paths->content, "");
		paths = paths->next;
	}
	free_lst(paths);
	if (files != NULL)
	{
		display_file(files, o, false);
	}
	free_file(files);
}
