#include "ft_ls.h"

/*
static void	print_args_values(t_flags *flags)
{
	printf ("-l: %d\n-r: %d\n-R: %d\n-a: %d\n-t: %d\n\n",
			flags->l_display, flags->reverse_sort, flags->recursive, flags->all, flags->time_sort);
	while (flags->file)
	{
		printf("Path: %s\n", flags->file->path);
		printf("Type: %c\n\n", flags->file->type);
		flags->file = flags->file->next;
	}
}
*/
void	simple_file_display(t_file *file)
{
	while (file != NULL)
	{
		ft_printf("{GREEN}%s{EOC}\n", file->path);
		file = file->next;
	}
}

void	print_not_found(t_file *not_found)
{
	while (not_found != NULL)
	{
		ft_printf("ls: {GREEN}%s{EOC}: No such file or directory\n", \
				  not_found->path);
		not_found = not_found->next;
	}
}

void	long_file_display(t_flags *f, t_size s)
{
	while (f->file != NULL)
	{
		if (!(f->l_display == false && f->file->path[0] == '.'))
		{
			print_access(f->file);
			print_links(f->file->statbuf.st_nlink, s.link_pad);
			print_usr(f->file->statbuf.st_uid, s.user_pad);
			print_grp(f->file->statbuf.st_gid, s.group_pad);
			if (f->file->type == CHARACTER || f->file->type == BLOCK)
			{
				print_special_id(f->file->statbuf.st_rdev, s.min_pad, s.maj_pad);
			}
			else
			{
				print_size(f->file->statbuf.st_size, s);
			}
			print_date(f->file->statbuf.st_mtime);
			ft_putendl(f->file->path);
		}
		f->file = f->file->next;
	}
}

int ft_ls(t_flags *flags)
{
	print_not_found(flags->not_found);
	if (flags->file != NULL)
	{
		if (flags->l_display == false)
			simple_file_display(flags->file);
		else
			long_file_display(flags, get_size(flags->file, flags));
		if (flags->dir != NULL)
			ft_putchar('\n');
	}
	/*if (flags->dir != NULL)
	{
		if (flags->l_display == false);
			//simple_dir_display(flags->dir);
		else
			long_dir_display(flags->dir);
	}*/
	return (true);
}

int main(int argc, char **argv)
{
	t_flags *flags;

	sort(argv);
	if ((flags = args_parsing(argv)) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	ft_ls(flags);
	//printf("dir: %ld\nfile: %ld\n", flags->dir_nb, flags->file_nb);
	//print_args_values(flags);
	free_flags(flags);
	return (true);
}