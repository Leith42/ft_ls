#include "ft_ls.h"

static void	print_args_values(t_flags *flags)
{
	printf ("-l: %d\n-r: %d\n-R: %d\n-a: %d\n-t: %d\n\n",
			flags->l_display, flags->reverse_sort, flags->recursive, flags->all, flags->time_sort);
	while (flags->file)
	{
		printf("Path: %s\n", flags->file->path);
		printf("Type: %c\n\n", flags->file->type);
		flags->file = flags->file->next;
	}
}

int simple_file_display(t_flags *flags)
{
	t_file *tmp;

	tmp = flags->file;
	while (flags->file)
	{
		if (flags->file->type != DIRECTORY)
		{
			ft_printf("%s\n", flags->file->path);
		}
		flags->file = flags->file->next;
	}
	flags->file = tmp;
	return (true);
}

void	print_not_found(t_file *f)
{
	while (f->path != NULL)
	{
		if (f->path->type == UNKNOWN)
		{

		}
	}
}
//TODO: SORTING ALGORITHM, ORGANISATION OF THE STRUCTURES.
int ft_ls(t_flags *flags)
{
	t_list *file;
	t_list *directory;

	print_not_found(flags->file);
	simple_file_display(flags);
	return (true);
}

int main(int argc, char **argv)
{
	t_flags *flags;

	if ((flags = args_parsing(argv)) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	ft_ls(flags);
	//print_args_values(flags);
	free_flags(flags);
	return (true);
}