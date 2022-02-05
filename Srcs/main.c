/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:22:32 by eydupray          #+#    #+#             */
/*   Updated: 2022/02/02 19:36:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fake_main(int ac, char **av, char **environ);

int main(int ac, char **av, char **environ)
{
	t_command	*commands;
	(void)ac;
	(void)av;

	//fake_main(ac,av,environ);
	char *line = readline("minishell : ");
	while (line)
	{
		commands = parsing(line, environ);
		line = readline("minishell : ");
	}
	write(1,"\n",1);
}
