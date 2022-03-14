CC = clang
INC = minishell.h
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
NAME = minishell

SRCS_MAIN	=		main.c 				\
					utils.c				\
					signal.c			\
					error.c 			

SRCS_ENVI	=		environnement.c		\
					get_path.c			

SRCS_EXEC	=		builtins.c			\
					exec_command.c		\
					redir.c				

SRCS_PARS	=		fct_tab.c			\
					tab_utils.c			\
					split_line.c		\
					parsing.c 			\
					ft_split.c 			\
					split_command.c 	\
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
