/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 13:23:53 by aazri             #+#    #+#             */
/*   Updated: 2017/09/11 13:23:54 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	access_cmp(t_file *a, t_file *b)
{
	if (a->statbuf.st_atime != b->statbuf.st_atime)
	{
		return (a->statbuf.st_atime < b->statbuf.st_atime);
	}
	return (ft_strcmp(a->path, b->path));
}
