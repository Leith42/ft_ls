/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:06:25 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:51:10 by aazri            ###   ########.fr       */
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
					&& argv[y][x] != 'R' && argv[y][x] != 't' && argv[y][x] != 'S'
					&& argv[y][x] != 'U')
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
			if (ft_strchr(argv[y], 'l') != NULL)
				o->l_display = true;
			if (ft_strchr(argv[y], 'r') != NULL)
				o->reverse_sort = true;
			if (ft_strchr(argv[y], 'R') != NULL)
				o->recursive = true;
			if (ft_strchr(argv[y], 'a') != NULL)
				o->all = true;
			if (ft_strchr(argv[y], 't') != NULL)
				o->time_sort = true;
			if (ft_strchr(argv[y], 'S') != NULL)
				o->size_sort = true;
			if (ft_strchr(argv[y], 'U') != NULL)
				o->creation_sort = true;
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
