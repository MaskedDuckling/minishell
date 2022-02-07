# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 16:16:08 by eydupray          #+#    #+#              #
#    Updated: 2022/02/05 01:22:19 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
INC = minishell.h
CFLAGS = -Wall -Werror -Wextra
-fsanitize=address

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
			fct_tab.c			

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
