/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:22:32 by eydupray          #+#    #+#             */
/*   Updated: 2022/02/01 18:28:36 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*for_for_access(char **path, char *join, int i, char *cmd)
{
	i = 0;
	if (!path)
		return (NULL);
	while (path[i] != 0)
	{
		if (ft_strend_is(path[i], "/") == 0)
			path[i] = ft_strjoin_free(path[i], "/");
		join = ft_strjoin(path[i], cmd);
		if (access(join, F_OK | X_OK) == 0)
		{
			free_command(path);
			return (join);
		}
		free(join);
		i++;
	}
	return (NULL);
}

char	*for_access(char *cmd, char **environ)
{
	int			i;
	char		**path;
	char		*join;

	i = -1;
	path = NULL;
	join = NULL;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], "PATH=", 5))
		{
			path = ft_split(environ[i] + 5, ':');
			break ;
		}	
	}
	join = for_for_access(path, join, i, cmd);
	if (join)
		return (join);
	free(cmd);
	if (path)
		free_command(path);
	return (NULL);
}

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_command *commands;

	char *line = readline("minishell : ");
	while (line)
	{
		commands = parsing(line, environ);
		//exec_command(commands);
		line = readline("minishell : ");
	}
	write(1,"\n",1);
}
