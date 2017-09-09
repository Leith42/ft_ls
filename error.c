#include "ft_ls.h"

void	print_error(char *error)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(error);
}