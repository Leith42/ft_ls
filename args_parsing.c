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

static int 	get_path_data(t_file *file)
{
	if ((lstat(file->path, &file->statbuf)) < 0)
		file->type = UNKNOWN;
	else if (S_ISREG(file->statbuf.st_mode) == true)
		file->type = REGULAR;
	else if (S_ISDIR(file->statbuf.st_mode) == true)
		file->type = DIRECTORY;
	else if (S_ISLNK(file->statbuf.st_mode) == true)
		file->type = SYMBOLIC;
	else if (S_ISBLK(file->statbuf.st_mode) == true)
		file->type = BLOCK;
	else if (S_ISCHR(file->statbuf.st_mode) == true)
		file->type = CHARACTER;
	else if (S_ISFIFO(file->statbuf.st_mode) == true)
		file->type = FIFO;
	else if (S_ISSOCK(file->statbuf.st_mode) == true)
		file->type = SOCKET;
	return (true);
}

static void	file_new(t_file **lst, t_file *new)
{
	t_file *tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int	stocks_path(char *argv, t_flags *flags)
{
	t_file *new_path;

	if ((new_path = ft_memalloc(sizeof(t_file))) == NULL
		|| (new_path->path = ft_strdup(argv)) == NULL)
	{
		return (false);
	}
	get_path_data(new_path);
	if (new_path->type == DIRECTORY)
		file_new(&flags->dir, new_path);
	else if (new_path->type == UNKNOWN)
		file_new(&flags->not_found, new_path);
	else
		file_new(&flags->file, new_path);
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
	return (flags->file == NULL ? stocks_path(".", flags) : true);
}

t_flags		*args_parsing(char **argv)
{
	t_flags *flags;

	if ((flags = ft_memalloc(sizeof(t_flags))) == NULL
		|| args_validity(argv) == false
		|| stocks_args(argv, flags) == false)
	{
		free_flags(flags);
		return (NULL);
	}
	return (flags);
}