/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_attribs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:33:19 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 18:33:25 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/xattr.h>
#include <sys/acl.h>

void	print_attribs(t_file *f)
{
	acl_t		acl;
	acl_entry_t	dummy;

	if (listxattr(f->path, 0, 0, XATTR_NOFOLLOW) > 0)
	{
		ft_putstr("@ ");
	}
	else if ((acl = acl_get_link_np(f->path, ACL_TYPE_EXTENDED)) != NULL)
	{
		if (acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) != -1)
		{
			ft_putstr("+ ");
		}
		acl_free(acl);
	}
	else
	{
		ft_putstr("  ");
	}
}
