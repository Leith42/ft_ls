/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:52:36 by aazri             #+#    #+#             */
/*   Updated: 2017/09/09 19:12:21 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))
# define DIRECTORY	'd'
# define REGULAR	'-'
# define BLOCK		'b'
# define CHARACTER	'c'
# define FIFO		'p'
# define SYMBOLIC	'l'
# define SOCKET		's'
# define UNKNOWN	'?'

typedef struct		s_file
{
	char			*path;
	char			*name;
	struct stat		statbuf;
	int				stat_statue;
	struct s_file	*next;
}					t_file;

typedef struct		s_options
{
	bool			l_display;
	bool			recursive;
	bool			reverse_sort;
	bool			time_sort;
	bool			all;
}					t_options;

typedef struct		s_size
{
	int				total;
	int				size_pad;
	int				link_pad;
	int				group_pad;
	int				user_pad;
	int				min_pad;
	int				maj_pad;
}					t_size;

/*
** PARSING:
*/

int					args_parsing(char **argv, t_options *o, t_list **paths);
t_size				get_size(t_file *f, t_options o);
int					stocks_path(char *argv, t_list **paths);
void				get_files(t_file **file, char *name, char *path);
void				handle_file(t_list *paths, t_options o);
void				handle_dir(t_list *paths, t_options o);
int					get_dir_content(t_file **f, struct dirent *dir, char *path);
void				recursive(t_file *f, t_options o);
t_file				*open_and_get(t_file *dir);

/*
** DISPLAY:
*/

void				display_file(t_file *f, t_options o, bool print_total);
void				simple_file_display(t_file *file, t_options o);
void				long_file_display(t_file *f, t_size s, t_options o);
void				long_dir_display();
void				print_grp(gid_t gid, int pad);
void				print_usr(uid_t uid, int pad);
void				print_links(int links, int pad);
void				print_access(t_file *f);
void				print_size(off_t size, t_size s);
void				print_special_id(dev_t id, int min_pad, int maj_pad);
void				print_date(time_t date);
void				print_name(t_file *f, t_options o);
void				print_attribs(t_file *f);
void				print_usage(char illegal);
void				print_not_found(t_list *f);

/*
** SORTING:
*/
void				reverse_sort(t_file **f);
int					lexic_cmp(t_file *a, t_file *b);
int					time_cmp(t_file *a, t_file *b);
void				ft_lstsort(t_list **list, int (*cmp)(t_list *a, t_list *b));
int					lst_alpha_cmp(t_list *a, t_list *b);
void				ft_mergesort(t_file **h, int (*cmp)(t_file *a, t_file *b));
int					r_lexic_cmp(t_file *a, t_file *b);

/*
** UTILS:
*/

void				free_file(t_file *f);
void				free_lst(t_list *paths);
void				print_error(char *error);

#endif
