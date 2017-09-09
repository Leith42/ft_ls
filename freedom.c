#include "ft_ls.h"

void	lstdel(void *content, size_t n)
{
	if (content != NULL)
	{
		ft_memdel(&content);
	}
	(void)n;
}

void	free_file(t_file *f)
{
	t_file *tmp;

	while (f)
	{
		tmp = f->next;
		free(f->path);
		free(f->name);
		free(f);
		f = tmp;
	}
}

void	free_lst(t_list *paths)
{
	ft_lstdel(&paths, lstdel);
}