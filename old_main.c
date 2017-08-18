#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "libft.h"

void	print_file_type(struct stat sb)
{
	printf("Type:\t\t\t");
	switch (sb.st_mode & S_IFMT)
	{
		case S_IFBLK:  printf("périphérique de bloc\n");      break;
		case S_IFCHR:  printf("périphérique de caractère\n"); break;
		case S_IFDIR:  printf("répertoire\n");                break;
		case S_IFIFO:  printf("FIFO/tube\n");                 break;
		case S_IFLNK:  printf("lien symbolique\n");           break;
		case S_IFREG:  printf("fichier ordinaire\n");         break;
		case S_IFSOCK: printf("socket\n");                    break;
		default:       printf("inconnu ?\n");                 break;
	}
}

char	*get_grpname(struct stat sb)
{
	struct group *grp;

	if ((grp = getgrgid(sb.st_gid)) == NULL)
	{
		perror("getgrgid");
		exit(EXIT_FAILURE);
	}
	return (grp->gr_name);
}

char	*get_pwuname(struct stat sb)
{
	struct passwd *pwuid;

	if ((pwuid = getpwuid(sb.st_uid)) == NULL)
	{
		perror("getpwuid");
		exit (EXIT_FAILURE);
	}
	return (pwuid->pw_name);
}

char	*get_last_modif(struct stat sb)
{
	return (ft_strsub(ctime(&sb.st_ctime), 4, 15));
}

int	main(int argc, char **argv)
{
	struct stat		sb;
	struct dirent	*s_dir;
	DIR 			*p_dir;

	if (argc != 2)
		return (0);
	/*if ((p_dir = opendir(argv[1])) == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	while ((s_dir = readdir(p_dir)) != NULL)
	{
		printf("%s\n", s_dir->d_name);
	}*/
	if ((stat(argv[1], &sb)) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	printf("Name: %s\n", argv[1]);
	print_file_type(sb);
	printf("File Permissions: \t");
	printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
	printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
	printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
	printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
	printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
	printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
	printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
	printf( (sb.st_mode & S_IROTH) ? "r" : "-");
	printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
	printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n");
	printf("Owner: \t\t\t%s\n", get_pwuname(sb));
	printf("Group: \t\t\t%s\n", get_grpname(sb));
	printf("Number of links: \t%ld\n", sb.st_nlink);
	printf("File size: \t\t%ld bytes\n", sb.st_size);
	printf("File inode: \t\t%ld\n", sb.st_ino);
	printf("Last modification: \t%s\n", get_last_modif(sb));
	printf("The file %s a symbolic link.\n", (S_ISLNK(sb.st_mode)) ? "is" : "is not");
}