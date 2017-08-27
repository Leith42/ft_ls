#include "ft_ls.h"

void	print_error(t_error err, char *s)
{
	if (err == NOT_FOUND)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", s);
	}
}
