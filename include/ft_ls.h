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

# define DIRECTORY	'd'
# define REGULAR	'-'
# define BLOCK		'b'
# define CHARACTER	'c'
# define FIFO		'p'
# define SYMBOLIC	'l'
# define SOCKET		's'
# define UNKNOWN	'?'

typedef enum 	e_error
{
	NOT_FOUND
}				t_error;

typedef	struct	s_file
{
	char			type;
	char			*path;
	//char			*name;
	struct stat		statbuf;
	struct s_file	*next;
}				t_file;

typedef	struct	s_flags
{
	bool		l_display;
	bool		recursive;
	bool		reverse_sort;
	bool		time_sort;
	bool		all;
	t_file		*file;
	size_t		n_file;
}				t_flags;

/*
** PARSING:
*/

t_flags		*args_parsing(char **argv);

/*
** UTILS:
*/

void		free_flags(t_flags *f);
void		print_error(t_error err, char *s);

#endif
