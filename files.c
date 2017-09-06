#include "ft_ls.h"

void	long_file_display(t_file *f, t_size s, t_options o)
{
	if (ft_strcmp(f->path, f->name) != 0)
	{
		ft_printf("total %d\n", s.total);
	}
	while (f != NULL)
	{
		if (!(f->name[0] == '.' && o.all == false))
		{
			print_access(f);
			print_links(f->statbuf.st_nlink, s.link_pad);
			print_usr(f->statbuf.st_uid, s.user_pad);
			print_grp(f->statbuf.st_gid, s.group_pad);
			if (S_ISBLK(f->statbuf.st_mode) || S_ISCHR(f->statbuf.st_mode))
			{
				print_special_id(f->statbuf.st_rdev, s.min_pad, s.maj_pad);
			}
			else
			{
				print_size(f->statbuf.st_size, s);
			}
			print_date(f->statbuf.st_mtime);
			print_name(f->name, f->statbuf.st_mode);
		}
		f = f->next;
	}
}

void	simple_file_display(t_file *file, t_options o)
{
	while (file != NULL)
	{
		if (!(o.all == false && file->name[0] == '.'))
		{
			print_name(file->name, file->statbuf.st_mode);
		}
		file = file->next;
	}
}

void	display_file(t_file *f, t_options o)
{
	sort(&f, path_cmp);
	if (o.time_sort == true)
	{
		sort(&f, time_cmp);
	}
	if (o.reverse_sort == true)
	{
		reverse_sort(&f);
	}
	if (o.l_display == true)
	{
		long_file_display(f, get_size(f, o), o);
	}
	else
	{
		simple_file_display(f, o);
	}
	if (o.recursive == true)
	{
		recursive(f, o);
	}
}

void	handle_file(t_list *paths, t_options o)
{
	t_file *files;

	files = NULL;
	o.all = true;
	while (paths != NULL)
	{
		get_files(&files, paths->content, "");
		paths = paths->next;
	}
	free_lst(paths);
	if (files != NULL)
	{
		display_file(files, o);
	}
	free_file(&files);
}