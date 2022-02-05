/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:22:32 by eydupray          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/02 19:36:18 by user42           ###   ########.fr       */
=======
/*   Updated: 2022/02/04 16:58:22 by maskedduck       ###   ########.fr       */
>>>>>>> 57d8f1f5d195a933d694eabbdb826aae65f21120
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fake_main(int ac, char **av, char **environ);

int main(int ac, char **av, char **environ)
{
<<<<<<< HEAD
	t_command	*commands;
	(void)ac;
	(void)av;

	//fake_main(ac,av,environ);
	char *line = readline("minishell : ");
=======
	(void)ac;
	(void)environ;
	ft_echo(++av);
	//fake_main(ac,av,environ);
	/*char *line = readline("minishell : ");
>>>>>>> 57d8f1f5d195a933d694eabbdb826aae65f21120
	while (line)
	{
		commands = parsing(line, environ);
		line = readline("minishell : ");
	}
	write(1,"\n",1);
}
