/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:22:32 by eydupray          #+#    #+#             */
/*   Updated: 2022/02/07 15:29:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	char *line;
	t_command *commands;
	t_envi *envi;

	envi = environnement(environ);
	line = readline("minishell : ");
	while (line)
	{
		commands = parsing(line, envi);
		if (!ft_strcmp(commands[0].argv[0], "exit"))
			break;
		exec_command(commands);
		line = readline("minishell : ");
	}
	write(1,"\n",1);
}