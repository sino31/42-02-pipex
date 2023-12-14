NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_SRCS = libft-utils/ft_strlen.c libft-utils/ft_strcmp.c libft-utils/ft_strncmp.c \
			 libft-utils/ft_strdup.c libft-utils/ft_strjoin.c libft-utils/ft_split.c \
			 libft-utils/ft_strchr.c libft-utils/ft_strlcpy.c

GNL_SRCS = gnl/get_next_line.c

PIPEX_SRCS = src/pipex_utils.c src/get_cmd_path.c src/cmd_handler.c \
             src/heredoc.c src/main.c

SRCS = $(LIBFT_SRCS) $(GNL_SRCS) $(PIPEX_SRCS)
OBJS = $(SRCS:.c=.o)

INCLUDES = includes/pipex.h gnl/get_next_line.h

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
