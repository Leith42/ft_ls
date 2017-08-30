#include "ft_ls.h"

static int myCompare (const void * a, const void * b)
{
	return (ft_strcmp (*(const char **) a, *(const char **) b));
}

static void	swap(char **a, char **b)
{
	void *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int is_sort(char **tab)
{
	int y;

	y = 1;
	while (tab[y] != NULL)
	{
		if (tab[y + 1] && strcmp(tab[y], tab[y + 1]) > 0)
			return (false);
		y++;
	}
	return (true);
}

void	sort(char **tab)
{
	int 	y;

	while (is_sort(tab) == false)
	{
		y = 1;
		while (tab[y] != NULL)
		{
			if (tab[y + 1] && strcmp(tab[y], tab[y + 1]) > 0)
				swap(&tab[y], &tab[y + 1]);
			y++;
		}
	}
}