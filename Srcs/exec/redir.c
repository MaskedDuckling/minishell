/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:59 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 17:40:00 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(char *line, int j)
{
	int	i;

	i = j;
	while (line[i] && ((line[i] >= '0' && line[i] <= '9')
			|| (line[i] >= 'a' && line[i] <= 'z')
			|| (line[i] >= 'A' && line[i] <= 'Z')
			|| (line[i] == '_')))
		i++;
	return (i - j);
}

int	type_four(t_command command)
{
	char	*line;
	int		tube[2];
	int		i;
	char	*name;
	char	*path;

	pipe(tube);
	line = readline("> ");
	while (ft_strcmp(line, command.redi->cont))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
			{
				name = ft_strndup(line + i + 1, get_len(line, i + 1));
				path = src_envi(name, command.envi);
				write(tube[1], path, ft_strlen(path));
				i += ft_strlen(name);
				free(name);
			}
			else
				write(tube[1], &line[i], 1);
			i++;
		}
		write(tube[1], "\n", 1);
		line = readline("> ");
	}
	close(tube[1]);
	return (tube[0]);
}

void	ft_redi(t_command command)
{
	char	*path;
	int		type;
	int		stin;
	int		stout;
	char	**envi;

	type = 0;
	path = NULL;
	stin = STDIN_FILENO;
	stout = STDOUT_FILENO;
	while (command.redi)
	{
		if (command.redi->type == 1)
			stout = open(command.redi->cont, O_WRONLY | O_CREAT, 0644);
		else if (command.redi->type == 2)
			stout = open(command.redi->cont, O_APPEND | O_WRONLY
					| O_CREAT, 0644);
		else if (command.redi->type == 3)
			stin = open(command.redi->cont, O_RDONLY | O_CREAT, 0644);
		else if (command.redi->type == 4)
			stin = type_four(command);
		if (!command.redi->next)
			break ;
		command.redi = command.redi->next;
	}
	envi = join_envi(command.envi);
	if (command.argv[0])
	{
		path = for_access(command.argv[0], envi);
		dup2(stin, STDIN_FILENO);
		dup2(stout, STDOUT_FILENO);
		execve(path, command.argv, envi);
		free_process(command);
		write(2, "minishell erreur : commande introuvable\n", 40);
	}
	destroy_env(command.envi);
	free_command(envi);
	free(path);
	exit(127);
}
