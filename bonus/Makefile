NAME = pipex

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra



SRCS		= main.c \
				child.c \
				files.c \
				utils.c \
				free.c \
				functions.c \
				ft_printf.c \
				ft_printf_utils.c \
				ft_putstr_fd.c \
				ft_strncmp.c \
				get_next_line.c \

OBJS		= $(SRCS:.c=.o)

RM 			:= rm -rf
MAKEFLAGS	+= --no-print-directory
all: $(NAME) 

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:

	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: 
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re
