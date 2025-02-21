NAME = pipex

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra



SRCS		= main.c \
				child.c \
				utils.c \
				free.c \
				functions.c \
				ft_printf.c \
				ft_printf_utils.c \

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
