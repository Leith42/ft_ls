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
			//ft_memdel((void **)&tmp->name);
			ft_memdel((void **)&tmp);
			//free((void *)tmp->name);
			//free(tmp);
		}
		//free(f);
		ft_memdel((void **)&f);
	}
}