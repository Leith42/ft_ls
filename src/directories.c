/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:04:25 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:05:59 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*open_and_get(t_file *dir)
{
	DIR				*p_dir;
	struct dirent	*s_dir;
	t_file			*dir_content;

	dir_content = NULL;
	if ((p_dir = opendir(dir->path)) != NULL)
	{
		while ((s_dir = readdir(p_dir)) != NULL)
		{
			get_dir_content(&dir_content, s_dir, ft_strjoin(dir->path, "/"));
		}
		closedir(p_dir);
	}
	else
	{
		print_error(dir->name);
	}
	return (dir_content);
}

void		handle_dir_content(t_file *dir, t_options o)
{
	t_file	*dir_content;
	t_file	*dir_tmp;
	bool	endl;
	bool	manydir;

	dir_tmp = dir;
	endl = false;
	manydir = dir->next != NULL ? true : false;
	while (dir != NULL)
	{
		endl == true ? ft_putchar('\n') : 0;
		manydir == true ? ft_printf("%s:\n", dir->name) : 0;
		if ((dir_content = open_and_get(dir)) != NULL)
		{
			if (o.all == false && dir_content->next->next == NULL)
				display_file(dir_content, o, false);
			else
				display_file(dir_content, o, true);
		}
		dir = dir->next;
		endl = true;
	}
	free_file(dir_tmp);
}

void		sort_dir(t_file *dir, t_options o)
{
	if (o.size_sort == true)
	{
		ft_mergesort(&dir, size_cmp);
		if (o.reverse_sort == true)
			reverse_sort(&dir);
	}
	else if (o.time_sort == true)
	{
		ft_mergesort(&dir, time_cmp);
		if (o.reverse_sort == true)
			reverse_sort(&dir);
	}
	else if (o.creation_sort == true)
	{
		ft_mergesort(&dir, creation_cmp);
		if (o.reverse_sort == true)
			reverse_sort(&dir);
	}
	else if (o.reverse_sort == true)
		ft_mergesort(&dir, r_lexic_cmp);
	else
		ft_mergesort(&dir, lexic_cmp);
}

void		handle_dir(t_list *paths, t_options o)
{
	t_file *dir;
	t_file *test;

	dir = NULL;
	while (paths != NULL)
	{
		get_files(&dir, paths->content, "");
		paths = paths->next;
	}
	free_lst(paths);
	test = dir;
	sort_dir(dir, o);
	dir = test;
	handle_dir_content(dir, o);
}
