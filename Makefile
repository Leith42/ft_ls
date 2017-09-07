NAME = ft_ls
MAKEFLAGS += --silent
CC = gcc
LIBFT_PATH = ./libft/
LIBFT_BIN = $(LIBFT_PATH)libft.a
INCLUDE = ./include/
HEADER = -I$(INCLUDE) -I$(LIBFT_PATH)include/
CFLAGS = -Wall -Wextra -Werror $(HEADER)
SRC_PATH = ./
RM = rm -f

SRC_FILES = \
		directories.c \
		files.c \
		main.c \
		freedom.c \
		printer.c \
		printer2.c \
		recursive.c \
		error.c \
		size.c \
		struct_manager.c \
		list_sort.c \
		file_sort.c \
		args_parsing.c \

SRC_OBJ = $(SRC_FILES:.c=.o)
SRC = $(addprefix $(SRC_PATH), $(SRC_OBJ))

all: $(NAME)

$(NAME): $(SRC_OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LIBFT_BIN)
	echo "\033[1;34m$(NAME)\t\t\033[1;33mCompilation\t\033[0;32m[OK]\033[0m"

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(SRC)
	echo "\033[1;34m${NAME}\t\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	echo "\033[1;34m${NAME}\t\t\033[1;33mCleaning exe\t\033[0;32m[OK]\033[0m"

re: fclean all

.PHONY: all clean fclean re
