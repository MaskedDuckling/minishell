CC = gcc
INC = minishell.h
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
NAME = minishell

SRCS_MAIN	=		main.c 				\
					utils1.c				\
					utils2.c			\
					signal.c			\
					error.c 			

SRCS_ENVI	=		environnement.c		\
					get_path.c			

SRCS_EXEC	=		builtins1.c		\
					builtins2.c		\
					builtins_utils.c	\
					check_builtins.c	\
					exec_command.c		\
					exec_command_utils.c		\
					redir1.c			\
					redir2.c				

SRCS_PARS	=		fct_tab1.c			\
					fct_tab2.c		\
					tab_utils1.c			\
					tab_utils2.c		\
					split_line.c		\
					parsing.c 			\
					ft_split.c 			\
					parse_commands.c 	\
					check_line.c

SRCS =	${addprefix Srcs/main/,${SRCS_MAIN}}	\
		${addprefix Srcs/envi/,${SRCS_ENVI}}	\
		${addprefix Srcs/exec/,${SRCS_EXEC}}	\
		${addprefix Srcs/pars/,${SRCS_PARS}}	

OBJS = ${SRCS:.c=.o}


all:    $(NAME)

$(NAME):	$(OBJS) 
		$(CC) $(OBJS) $(CFLAGS) -lreadline -o $(NAME)

clean:
		rm -f $(OBJS) $(OBJS_EXEC) $(OBJS_PARS) $(OBJS_ENVI)

fclean: clean
		rm -f $(NAME)

po:		all clean

re:		fclean all

.PHONY: all clean fclean re
