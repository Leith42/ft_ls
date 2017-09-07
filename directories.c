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
		print_error(dir->path);
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
		if ((dir_content = open_and_get(dir)) != NULL)
		{
			endl == true ? ft_putchar('\n') : NULL;
			if (manydir == true)
				ft_printf("%s:\n", dir->name);
			if (o.all == false && dir_content->next->next == NULL)
				display_file(dir_content, o, false);
			else
				display_file(dir_content, o, true);
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
	if (o.time_sort == true)
	{
		MergeSort(&dir, time_cmp);
		if (o.reverse_sort == true)
		{
			reverse_sort(&dir);
		}
	}
	else if (o.reverse_sort == true)
	{
		MergeSort(&dir, r_lexic_cmp);
	}
	else
	{
		MergeSort(&dir, lexic_cmp);
	}
	handle_dir_content(dir, o);
}