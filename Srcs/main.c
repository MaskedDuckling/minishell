/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:22:32 by eydupray          #+#    #+#             */
/*   Updated: 2022/02/04 16:58:22 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fake_main(int ac, char **av, char **environ);

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)environ;
	ft_echo(++av);
	//fake_main(ac,av,environ);
	/*char *line = readline("minishell : ");
	while (line)
	{
		commands = parsing(line, environ);
		line = readline("minishell : ");
	}
	write(1,"\n",1);*/
}
