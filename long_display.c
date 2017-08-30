#include "ft_ls.h"

void	print_size(off_t size, int pad)
{
	ft_printf("%*d ", pad, size);
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

void	print_usr(uid_t uid, int pad)
{
	struct passwd *usr;

	if ((usr = getpwuid(uid)) != NULL)
	{
		ft_printf("%*s  ", pad, usr->pw_name);
	}
	else
	{
		ft_printf("%*d  ", pad, uid);
	}
}

void	print_links(int links, int pad)
{
	ft_printf("%*d ", pad, links);
}

void	print_access(t_file *f)
{
	ft_putchar(f->type);
	ft_putchar((f->statbuf.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((f->statbuf.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((f->statbuf.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((f->statbuf.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((f->statbuf.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((f->statbuf.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((f->statbuf.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((f->statbuf.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((f->statbuf.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}