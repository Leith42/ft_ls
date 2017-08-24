#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>

/*
** STRUCTS:
*/

typedef	enum	e_type
{
	UNKNOWN,
	DIRECTORY,
	REGULAR,
	BLOCK,
	CHARACTER,
	NETWORK,
	FIFO,
	SYMBOLIC,
	SOCKET
}				t_type;

typedef	struct	s_path
{
	const char		*name;
	struct stat		statbuf;
	struct s_path	*next;
}				t_path;

typedef	struct	s_flags
{
	bool		l_display;
	bool		recursive;
	bool		reverse_sort;
	bool		time_sort;
	bool		all;
	t_path		*paths;
	size_t		n_paths;
}				t_flags;

/*
** PARSING:
*/

t_flags		*args_parsing(char **argv);

/*
** UTILS:
*/

void		free_flags(t_flags *f);

#endif
