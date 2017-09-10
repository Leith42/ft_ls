/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:07:00 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:52:11 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	lexic_cmp(t_file *a, t_file *b)
{
	return (ft_strcmp(a->path, b->path));
}

int	r_lexic_cmp(t_file *a, t_file *b)
{
	return (-(ft_strcmp(a->path, b->path)));
}

int	size_cmp(t_file *a, t_file *b)
{
	if (b->statbuf.st_size > a->statbuf.st_size)
		return (1);
	if (b->statbuf.st_size < a->statbuf.st_size)
		return (-1);
	return (ft_strcmp(a->path, b->path));
}

int	creation_cmp(t_file *a, t_file *b)
{
	if (a->statbuf.st_birthtimespec.tv_nsec != b->statbuf.st_birthtimespec.tv_nsec)
	{
		return (a->statbuf.st_birthtimespec.tv_nsec < b->statbuf.st_birthtimespec.tv_nsec);
	}
	if (a->statbuf.st_birthtimespec.tv_sec != b->statbuf.st_birthtimespec.tv_sec)
	{
		return (a->statbuf.st_birthtimespec.tv_sec < b->statbuf.st_birthtimespec.tv_sec);
	}
	return (ft_strcmp(a->path, b->path));
}

int	time_cmp(t_file *a, t_file *b)
{
	if (a->statbuf.st_mtimespec.tv_sec != b->statbuf.st_mtimespec.tv_sec)
	{
		return (a->statbuf.st_mtimespec.tv_sec \
			< b->statbuf.st_mtimespec.tv_sec);
	}
	if (a->statbuf.st_mtimespec.tv_nsec != b->statbuf.st_mtimespec.tv_nsec)
	{
		return (a->statbuf.st_mtimespec.tv_nsec \
			< b->statbuf.st_mtimespec.tv_nsec);
	}
	return (ft_strcmp(a->path, b->path));
}
