#include "ft_ls.h"

void	print_date(time_t date)
{
	char *str;

	if ((str = ft_strsub(ctime(&date), 4, 12)) == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_putstr(str);
	ft_putchar(' ');
	free(str);
}

void	print_special_id(dev_t id, int min_pad, int maj_pad)
{
	ft_printf("%*d, %*d ", maj_pad, major(id), min_pad, minor(id));
}

void	print_size(off_t size, t_size s)
{
	if (s.maj_pad > 0 || s.min_pad > 0)
	{
		if (s.maj_pad + s.min_pad + 2 > s.size_pad)
		{
			s.size_pad = s.maj_pad + s.min_pad + 2;
		}
	}
	ft_printf("%*ld ", s.size_pad, size);
}

void	print_grp(gid_t gid, int pad)
{
	struct group *g;

	if ((g = getgrgid(gid)) != NULL)
	{
		ft_printf("%*s  ", pad, g->gr_name);
	}
	else
	{
		ft_printf("%*d  ", pad, gid);
	}
}