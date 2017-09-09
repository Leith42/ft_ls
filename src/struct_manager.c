/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:22:50 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:29:37 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*new_file(char *name, char *path)
{
	t_file *new;

	if ((new = ft_memalloc(sizeof(t_file))) == NULL
		|| (new->path = ft_strjoin(path, name)) == NULL
		|| (new->name = ft_strdup(name)) == NULL)
	{
		print_error(path);
		free_file(new);
		exit(EXIT_FAILURE);
	}
	new->stat_statue = lstat(new->path, &new->statbuf);
	return (new);
}

int				get_dir_content(t_file **file, struct dirent *dir, char *path)
{
	t_file	*list;

	list = *file;
	if (dir == NULL)
	{
		ft_strdel(&path);
		return (false);
	}
	if (path == NULL)
	{
		print_error(dir->d_name);
		exit(EXIT_FAILURE);
	}
	if (list)
	{
		while (list->next)
		{
			list = list->next;
		}
		list->next = new_file(dir->d_name, path);
	}
	else
		*file = new_file(dir->d_name, path);
	ft_strdel(&path);
	return (true);
}

void			get_files(t_file **file, char *name, char *path)
{
	t_file *tmp;

	tmp = *file;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_file(name, path);
	}
	else
	{
		*file = new_file(name, path);
	}
}
