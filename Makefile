NAME = minishell
CC = clang
INC = minishell.h
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

SRCS	=	main.c 				\
			ft_split.c 			\
			utils.c				\
			error.c 			\
			parsing.c 			\
			split_command.c 	\
			split_line.c		\
			get_path.c			\
			exec_command.c		\
			environnement.c		\
			builtins.c			\
			fct_tab.c			\
			redir.c			\
			tab_utils.c
			

OBJS = ${addprefix Srcs/,${SRCS:.c=.o}}

all:    $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) $(CFLAGS) -lreadline -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

po:		all clean

re:		fclean all

.PHONY: all clean fclean re
