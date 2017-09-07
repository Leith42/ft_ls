#include "ft_ls.h"

void	print_denied(t_file *dir, bool endl, bool manydir)
{
	if (endl == true)
		ft_putchar('\n');
	if (manydir == true)
		printf("%");
}

void	print_error(char *error)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(error);
}
