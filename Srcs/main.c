/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:22:32 by eydupray          #+#    #+#             */
/*   Updated: 2022/02/01 20:41:00 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_command *commands;

	char *line = readline("minishell : ");
	while (line)
	{
		commands = parsing(line, environ);
		//exec_command(commands, environ);
		line = readline("minishell : ");
	}
	write(1,"\n",1);
}
