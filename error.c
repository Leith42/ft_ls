#include "ft_ls.h"

void	print_error(char *error, char *name)
{
	ft_putstr_fd(name, 2);
	perror(error);
}
