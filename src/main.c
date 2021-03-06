/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:48:56 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:50:04 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_usage(char illegal)
{
	ft_printf("ft_ls: illegal option -- %c\n", illegal);
	ft_putendl("usage: ft_ls [-lrRatSUu] [file ...]");
}

static void	filter(t_list **files, t_list **directories, \
	t_list **not_found, t_list *paths)
{
	DIR *d;

	while (paths != NULL)
	{
		if ((d = opendir(paths->content)) == NULL)
		{
			if (errno == ENOTDIR)
				stocks_path(paths->content, files);
			else if (errno == EACCES)
				stocks_path(paths->content, directories);
			else
				stocks_path(paths->content, not_found);
		}
		else
		{
			stocks_path(paths->content, directories);
			if (closedir(d) < 0)
				print_error(paths->content);
		}
		paths = paths->next;
	}
}

void		ft_ls(t_list *paths, t_options o)
{
	t_list *files;
	t_list *directories;
	t_list *not_found;

	files = NULL;
	directories = NULL;
	not_found = NULL;
	filter(&files, &directories, &not_found, paths);
	free_lst(paths);
	if (not_found != NULL)
	{
		print_not_found(not_found);
		free_lst(not_found);
	}
	if (files != NULL)
		handle_file(files, o);
	if (files != NULL && directories != NULL)
		ft_putchar('\n');
	if (directories != NULL)
		handle_dir(directories, o);
	free_lst(directories);
	free_lst(files);
}

int			main(int argc, char **argv)
{
	t_options	o;
	t_list		*paths;

	paths = NULL;
	ft_bzero(&o, sizeof(t_options));
	if (args_parsing(argv, &o, &paths) == false)
	{
		exit(EXIT_FAILURE);
	}
	ft_ls(paths, o);
	(void)argc;
	return (true);
}
