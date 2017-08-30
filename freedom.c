#include "ft_ls.h"

void	free_flags(t_flags *f)
{
	t_file *tmp;

	if (f != NULL)
	{
		while (f->file != NULL)
		{
			tmp = f->file;
			f->file = f->file->next;
			ft_memdel((void **)&tmp->path);
			ft_memdel((void **)&tmp);
		}
		while (f->dir != NULL)
		{
			tmp = f->dir;
			f->dir = f->dir->next;
			ft_memdel((void **)&tmp->path);
			ft_memdel((void **)&tmp);
		}
		while (f->not_found != NULL)
		{
			tmp = f->not_found;
			f->not_found = f->not_found->next;
			ft_memdel((void **)&tmp->path);
			ft_memdel((void **)&tmp);
		}
		ft_memdel((void **)&f);
	}
}