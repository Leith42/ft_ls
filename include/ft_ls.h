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
# include <stdbool.h>

# define major(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define minor(x)((int32_t)((x) & 0xffffff))
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
	t_file		*dir;
	t_file		*not_found;
	size_t		file_nb;
	size_t 		dir_nb;
}				t_flags;

typedef struct	s_size
{
	int 		total;
	int 		size_pad;
	int			link_pad;
	int 		group_pad;
	int 		user_pad;
	int 		min_pad;
	int 		maj_pad;
}				t_size;

/*
** PARSING:
*/

t_flags		*args_parsing(char **argv);

/*
** UTILS:
*/

void		free_flags(t_flags *f);
void		print_error(t_error err, char *s);

/*
** SORTING
*/

void		sort(char **tab);

void	print_grp(gid_t gid, int pad);
void	print_usr(uid_t uid, int pad);
void	print_links(int links, int pad);
void	print_access(t_file *f);
void	print_size(off_t size, t_size s);
void	print_special_id(dev_t id, int min_pad, int maj_pad);
void	print_date(time_t date);

t_size	get_size(t_file *f, t_flags *flags);
#endif
