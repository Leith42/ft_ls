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

/*static t_type get_path_type(struct stat statbuf)
{
	if (S_ISDIR(statbuf.st_mode) == true)
		return (DIRECTORY);
	else if (S_ISBLK(statbuf.st_mode) == true)
		return (BLOCK);
	else if (S_ISCHR(statbuf.st_mode) == true)
		return (CHARACTER);
	else if (S_ISFIFO(statbuf.st_mode) == true)
		return (FIFO);
	else if (S_ISLNK(statbuf.st_mode) == true)
		return (SYMBOLIC);
	else if (S_ISREG(statbuf.st_mode) == true)
		return (REGULAR);
	else if (S_ISSOCK(statbuf.st_mode) == true)
		return (SOCKET);
	else
		return (UNKNOWN);
}*/

static int 	get_path_data(t_path *path)
{
	if ((lstat(path->name, &path->statbuf)) < 0)
	{
		perror("stat");
		return (false);
	}
	return (true);
}

static int	stocks_path(char *argv, t_flags *flags)
{
	t_path *new_path;
	t_path *tmp;

	tmp = flags->paths;
	if ((new_path = ft_memalloc(sizeof(t_path))) == NULL
		|| (new_path->name = ft_strdup(argv)) == NULL)
	{
		return (false);
	}
	if (tmp == NULL)
	{
		flags->paths = new_path;
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_path;
	}
	flags->n_paths++;
	return (get_path_data(new_path));
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
				flags->l_display = 1;
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
	return (flags->paths == NULL ? stocks_path(".", flags) : true);
}

t_flags		*args_parsing(char **argv)
{
	t_flags *flags;

	if ((flags = ft_memalloc(sizeof(t_flags))) == NULL
		|| args_validity(argv) == false
		|| stocks_args(argv, flags) == false)
	{
		//free_flags(flags);
		return (NULL);
	}
	return (flags);
}