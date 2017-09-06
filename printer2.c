#include "ft_ls.h"

void 	print_name(const char *name, int type)
{
	if (S_ISDIR(type))
	{
		ft_printf("{BLUE}%s{EOC}\n", name);
	}
	else if (S_ISREG(type))
	{
		ft_printf("{GREEN}%s{EOC}\n", name);
	}
	else if (S_ISBLK(type) || S_ISCHR(type))
	{
		ft_printf("%s%s%s\n", "\x1b[33m", name, "\x1b[0m");
	}
	else if (S_ISLNK(type))
	{
		ft_printf("%s%s%s\n", "\x1b[35m", name, "\x1b[0m");
	}
	else
	{
		ft_putendl(name);
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

void	print_type(int type)
{
	if (S_ISDIR(type))
		ft_putchar(DIRECTORY);
	else if (S_ISREG(type))
		ft_putchar(REGULAR);
	else if (S_ISCHR(type))
		ft_putchar(CHARACTER);
	else if (S_ISBLK(type))
		ft_putchar(BLOCK);
	else if (S_ISFIFO(type))
		ft_putchar(FIFO);
	else if (S_ISSOCK(type))
		ft_putchar(SOCKET);
	else if (S_ISLNK(type))
		ft_putchar(SYMBOLIC);
	else
		ft_putchar(UNKNOWN);
}

void	print_access(t_file *f)
{
	print_type(f->statbuf.st_mode);
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