#include "ft_ls.h"

void	recursive(t_file *f, t_options o)
{
	t_file *content;

	while (f != NULL)
	{
		if (S_ISDIR(f->statbuf.st_mode)
			&& !(o.all == false && f->name[0] == '.')
			&& ft_strcmp(".", f->name) != 0
			&& ft_strcmp("..", f->name) != 0)
		{
			if ((content = open_and_get(f)) != NULL)
			{
				ft_printf("\n%s:\n", f->path);
				display_file(content, o);
				free_file(&content);
			}
		}
		f = f->next;
	}
}