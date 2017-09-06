#include "ft_ls.h"

void	lstdel(void *content, size_t n)
{
	if (content != NULL)
	{
		ft_memdel(&content);
	}
	(void)n;
}

void	free_file(t_file **f)
{
	void *tmp;

	while (f && *f)
	{
		tmp = *f;
		ft_strdel(&(*f)->path);
		ft_strdel(&(*f)->name);
		*f = (*f)->next;
		ft_memdel(&tmp);
	}
}

void	free_lst(t_list *paths)
{
	ft_lstdel(&paths, lstdel);
}