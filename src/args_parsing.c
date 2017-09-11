/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:06:25 by aazri             #+#    #+#             */
/*   Updated: 2017/09/11 13:21:42 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	args_validity(char **argv)
{
	int x;
	int y;

	y = 1;
	while (argv[y] != NULL)
	{
		x = 0;
		if (argv[y][x] == '-')
		{
			while (argv[y][++x])
			{
				if (argv[y][x] != 'l' && argv[y][x] != 'a' && argv[y][x] != 'r'
					&& argv[y][x] != 'R' && argv[y][x] != 't'
					&& argv[y][x] != 'S' && argv[y][x] != 'U'
					&& argv[y][x] != 'u')
				{
					print_usage(argv[y][x]);
					return (false);
				}
			}
		}
		y++;
	}
	return (true);
}

int			stocks_path(char *argv, t_list **paths)
{
	t_list *tmp;

	tmp = *paths;
	if (tmp == NULL)
	{
		if ((*paths = ft_lstnew(argv, ft_strlen(argv) + 1)) == NULL)
		{
			print_error(argv);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		if ((tmp->next = ft_lstnew(argv, ft_strlen(argv) + 1)) == NULL)
		{
			print_error(argv);
			exit(EXIT_FAILURE);
		}
	}
	return (true);
}

static int	stocks_args(char **argv, t_options *o, t_list **paths)
{
	int y;

	y = 1;
	while (argv[y] != NULL)
	{
		if (argv[y][0] == '-' && argv[y][1] != '\0')
		{
			o->l_display = ft_strchr(argv[y], 'l') != 0 ? true : o->l_display;
			o->reverse_sort = ft_strchr(argv[y], 'r') \
			!= 0 ? true : o->reverse_sort;
			o->recursive = ft_strchr(argv[y], 'R') != 0 ? true : o->recursive;
			o->all = ft_strchr(argv[y], 'a') != 0 ? true : o->all;
			o->time_sort = ft_strchr(argv[y], 't') != 0 ? true : o->time_sort;
			o->size_sort = ft_strchr(argv[y], 'S') \
			!= 0 ? true : o->size_sort;
			o->creation_sort = ft_strchr(argv[y], 'U') \
			!= 0 ? true : o->creation_sort;
			o->access_sort = ft_strchr(argv[y], 'u') \
			!= 0 ? true : o->access_sort;
		}
		else
			stocks_path(argv[y], paths);
		y++;
	}
	return (*paths == NULL ? stocks_path(".", paths) : true);
}

int			args_parsing(char **argv, t_options *o, t_list **paths)
{
	if (args_validity(argv) == false || stocks_args(argv, o, paths) == false)
	{
		return (false);
	}
	return (true);
}
