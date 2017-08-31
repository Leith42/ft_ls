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
	if (s.maj_pad + s.min_pad > s.size_pad)
	{
		s.size_pad = s.maj_pad + s.min_pad + 2;
	}
	ft_printf("%*d ", s.size_pad, size);
}

void	print_grp(gid_t gid, int pad)
{
	struct group *g;

	if ((g = getgrgid(gid)) != NULL)
	{
		ft_printf("%-*s  ", pad, g->gr_name);
	}
	else
	{
		ft_printf("%-*d  ", pad, gid);
	}
}

void	print_usr(uid_t uid, int pad)
{
	struct passwd *usr;

	if ((usr = getpwuid(uid)) != NULL)
	{
		ft_printf("%-*s  ", pad, usr->pw_name);
	}
	else
	{
		ft_printf("%-*d  ", pad, uid);
	}
}

void	print_links(int links, int pad)
{
	ft_printf("%-*d ", pad, links);
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