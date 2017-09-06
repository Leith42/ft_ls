#include "ft_ls.h"

t_file	*open_and_get(t_file *dir)
{
	DIR *p_dir;
	struct dirent *s_dir;
	t_file *dir_content;

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
		print_error(dir->path, "ft_ls: ");
	}
	return (dir_content);
}

void	handle_dir_content(t_file *dir, t_options o)
{
	t_file *dir_content;
	t_file *dir_tmp;
	bool endl;
	bool manydir;

	dir_tmp = dir;
	endl = false;
	manydir = dir->next != NULL ? true : false;
	while (dir != NULL)
	{
		dir_content = open_and_get(dir);
		if (dir_content != NULL)
		{
			endl == true ? ft_putchar('\n') : NULL;
			if (manydir == true)
			{
				ft_printf("%s:\n", dir->name);
			}
			display_file(dir_content, o);
			free_file(&dir_content);
		}
		dir = dir->next;
		endl = true;
	}
	free_file(&dir_tmp);
}

void	handle_dir(t_list *paths, t_options o)
{
	t_file *dir;

	dir = NULL;
	while (paths != NULL)
	{
		get_files(&dir, paths->content, "");
		paths = paths->next;
	}
	free_lst(paths);
	sort(&dir, path_cmp);
	if (o.time_sort == true)
	{
		sort(&dir, time_cmp);
	}
	else if (o.reverse_sort == true)
	{
		reverse_sort(&dir);
	}
	handle_dir_content(dir, o);
}