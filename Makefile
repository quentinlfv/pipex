NAME 	= pipex
NAME_B	= pipex_bonus
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

SRC_PATH = mandatory/
OBJ_PATH = obj/
OBJ_PATH_B = obj/
BONUS_PATH = bonus/



SRC		= main.c \
		child.c \
		utils.c \
		free.c \
		functions.c \
		ft_printf.c \
		ft_printf_utils.c \

B_SRC	= 	main.c \
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
		get_next_line_utils.c \



SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
INCS		= -I ./includes/

B_SRCS		= $(addprefix $(SRC_PATH), $(B_SRC))
B_OBJ		= $(B_SRC:.c=.o)
B_OBJS		= $(addprefix $(OBJ_PATH), $(B_OBJ))

RM 			:= rm -rf
MAKEFLAGS	+= --no-print-directory

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
		$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH_B)%.o: $(BONUS_PATH)%.c 
		$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
		mkdir $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_B): $(OBJ_PATH_B) $(B_OBJS)
		$(CC) $(CFLAGS) $(B_OBJS) -o $(NAME_B)

bonus: $(NAME_B)

clean:
	$(RM) $(OBJS) $(OBJ_PATH)

fclean: clean
		$(RM) $(NAME) $(NAME_B)

re: 
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re bonus
