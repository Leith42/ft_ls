#include "ft_ls.h"

static void filter(t_list **files, t_list **directories, t_list *paths)
{
	DIR *d;

	while (paths != NULL)
	{
		if ((d = opendir(paths->content)) == NULL)
		{
			if (errno == ENOTDIR)
			{
				stocks_path(paths->content, files);
			}
			else
			{
				print_error(paths->content, "ft_ls: ");
			}
		}
		else
		{
			stocks_path(paths->content, directories);
			if (closedir(d) < 0)
			{
				print_error(paths->content, "ft_ls: ");
			}
		}
		paths = paths->next;
	}
}

void ft_ls(t_list *paths, t_options o)
{
	t_list *files;
	t_list *directories;

	files = NULL;
	directories = NULL;
	filter(&files, &directories, paths);
	free_lst(paths);
	if (files != NULL)
	{
		handle_file(files, o);
	}
	if (files != NULL && directories != NULL)
	{
		ft_putchar('\n');
	}
	if (directories != NULL)
	{
		handle_dir(directories, o);
	}
	free_lst(files);
	free_lst(directories);
}

int main(int argc, char **argv)
{
	t_options o;
	t_list *paths;

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