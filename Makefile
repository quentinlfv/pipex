NAME 	= pipex
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

SRC_PATH = mandatory/
OBJ_PATH = obj/



SRC		= main.c \
		child.c \
		utils.c \
		free.c \
		functions.c \
		ft_printf.c \
		ft_printf_utils.c \


SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
INCS		= -I ./includes/

RM 			:= rm -rf
MAKEFLAGS	+= --no-print-directory

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
		$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
		mkdir $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) $(OBJ_PATH)

fclean: clean
		$(RM) $(NAME)

re: 
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re
