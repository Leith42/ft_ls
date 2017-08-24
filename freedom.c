#include "ft_ls.h"

void	free_flags(t_flags *f)
{
	t_path *tmp;

	if (f != NULL)
	{
		while (f->paths != NULL)
		{
			tmp = f->paths;
			f->paths = f->paths->next;
			ft_memdel((void **)&tmp->name);
			ft_memdel((void **)&tmp);
			//free((void *)tmp->name);
			//free(tmp);
		}
		//free(f);
		ft_memdel((void **)&f);
	}
}