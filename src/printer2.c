/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:31:47 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:32:58 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define BUF_SIZE 1024

void	print_name(t_file *f, t_options o)
{
	ssize_t	len;
	char	link_buf[BUF_SIZE];

	if (S_ISDIR(f->statbuf.st_mode))
		ft_printf("%s%s%s\n", "\x1b[36m", f->name, "\x1b[0m");
	else if (S_ISLNK(f->statbuf.st_mode) && o.l_display == true)
	{
		if ((len = readlink(f->path, link_buf, BUF_SIZE - 1)) == -1)
		{
			print_error(f->path);
			exit(EXIT_FAILURE);
		}
		link_buf[len] = '\0';
		ft_printf("%s%s%s", "\x1b[35m", f->name, "\x1b[0m");
		ft_printf(" -> %s\n", link_buf, f->name, f->path);
	}
	else if (S_ISLNK(f->statbuf.st_mode))
		ft_printf("%s%s%s\n", "\x1b[35m", f->name, "\x1b[0m");
	else if (S_ISBLK(f->statbuf.st_mode) || S_ISCHR(f->statbuf.st_mode))
		ft_printf("%s%s%s\n", "\x1b[33m", f->name, "\x1b[0m");
	else if (S_ISSOCK(f->statbuf.st_mode))
		ft_printf("{GREEN}%s{EOC}\n", f->name);
	else
		ft_putendl(f->name);
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
	if (f->statbuf.st_mode & S_ISUID)
		ft_putchar(f->statbuf.st_mode & S_IXUSR ? 's' : 'S');
	else
		ft_putchar(f->statbuf.st_mode & S_IXUSR ? 'x' : '-');
	ft_putchar((f->statbuf.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((f->statbuf.st_mode & S_IWGRP) ? 'w' : '-');
	if (f->statbuf.st_mode & S_ISGID)
		ft_putchar(f->statbuf.st_mode & S_IXGRP ? 's' : 'S');
	else
		ft_putchar(f->statbuf.st_mode & S_IXGRP ? 'x' : '-');
	ft_putchar((f->statbuf.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((f->statbuf.st_mode & S_IWOTH) ? 'w' : '-');
	if (f->statbuf.st_mode & S_ISVTX)
		ft_putchar(f->statbuf.st_mode & S_IXOTH ? 't' : 'T');
	else
		ft_putchar((f->statbuf.st_mode & S_IXOTH) ? 'x' : '-');
}
