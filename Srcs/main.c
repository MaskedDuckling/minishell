/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:22:32 by eydupray          #+#    #+#             */
/*   Updated: 2022/02/07 14:17:26 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	char *line;
	t_command *commands;

	line = readline("minishell : ");
	while (line)
	{
		commands = parsing(line, environ);
		exec_command(commands);
		line = readline("minishell : ");
	}
	write(1,"\n",1);
}
