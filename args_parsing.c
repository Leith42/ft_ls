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
				if (argv[y][x] != 'l' && argv[y][x] != 'a'
					&& argv[y][x] != 'r' && argv[y][x] != 'R' && argv[y][x] != 't')
				{
					return (false);
				}
			}
		}
		y++;
	}
	return (true);
}

static int stocks_path(char *argv, t_flags *flags)
{
	t_list *new_path;
	t_list *tmp;

	tmp = flags->paths;
	if ((new_path = ft_memalloc(sizeof(new_path))) == NULL
		|| (new_path->content = ft_strdup(argv)) == NULL)
	{
		return (false);
	}
	new_path->content_size = ft_strlen(argv);
	if (tmp == NULL)
	{
		flags->paths = new_path;
	}
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_path;
	}
	return (true);
}

static int stocks_args(char **argv, t_flags *flags)
{
	int y;

	y = 1;
	while (argv[y] != NULL)
	{
		if (argv[y][0] == '-' && argv[y][1] != '\0')
		{
			if (ft_strchr(argv[y], 'l') != NULL)
				flags->details = 1;
			if (ft_strchr(argv[y], 'r') != NULL)
				flags->reverse_sort = 1;
			if (ft_strchr(argv[y], 'R') != NULL)
				flags->recursive = 1;
			if (ft_strchr(argv[y], 'a') != NULL)
				flags->all = 1;
			if (ft_strchr(argv[y], 't') != NULL)
				flags->time_sort = 1;
		}
		else
		{
			if (stocks_path(argv[y], flags) == false)
				return (false);
		}
		y++;
	}
	return (true);
}

t_flags		*args_parsing(char **argv)
{
	t_flags *flags;

	if ((flags = ft_memalloc(sizeof(flags))) == NULL
		|| args_validity(argv) == false
		|| stocks_args(argv, flags) == false)
	{
		return (NULL);
	}
	return (flags);
}