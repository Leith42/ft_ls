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
				ft_putchar('\n');
				ft_putstr(f->path);
				ft_putstr(":\n");
				if (o.all == false && content->next->next == NULL)
					display_file(content, o, false);
				else
					display_file(content, o, true);
			}
		}
		f = f->next;
	}
}