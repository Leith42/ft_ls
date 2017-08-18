#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

typedef	struct	s_flags
{
	bool		details;
	bool		recursive;
	bool		reverse_sort;
	bool		time_sort;
	bool		all;
	t_list		*paths;
}				t_flags;

t_flags		*args_parsing(char **argv);

#endif
