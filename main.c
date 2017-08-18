#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_flags *flags;

	if ((flags = args_parsing(argv)) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	printf ("-l: %d\n-r: %d\n-R: %d\n-a: %d\n-t: %d\n", flags->details, flags->reverse_sort, flags->recursive, flags->all, flags->time_sort);
	while (flags->paths)
	{
		puts(flags->paths->content);
		flags->paths = flags->paths->next;
	}
}