#include "ft_ls.h"

static void	print_args_values(t_flags *flags)
{
	printf ("-l: %d\n-r: %d\n-R: %d\n-a: %d\n-t: %d\n\n",
			flags->l_display, flags->reverse_sort, flags->recursive, flags->all, flags->time_sort);
	while (flags->paths)
	{
		printf("Path: %s\n", flags->paths->name);
		flags->paths = flags->paths->next;
	}
}

int main(int argc, char **argv)
{
	t_flags		*flags;
	struct stat	stat;

	if ((flags = args_parsing(argv)) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	//recursive(flags);
	print_args_values(flags);
	free_flags(flags);
}