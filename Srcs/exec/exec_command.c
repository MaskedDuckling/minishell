/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:58 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/21 15:22:45 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_process(t_command *command)
{
	int		i;
	t_redi	*mem_redi;

	while (command)
	{
		mem_redi = command->redi->next;
		i = 0;
		while (command->argv[i])
			free(command->argv[i++]);
		free(command->argv);
		free(command->redi->cont);
		free(command->redi);
		command->redi = mem_redi;
		command = command->next;
	}
	free(command);
}

char	*invalid_file(t_command *com, char **environ)
{
	char	*path;

	if (com->argv && com->argv[0] && com->argv[0][0] == '\0')
	{
		destroy_com(com);
		free_env(environ);
		path = NULL;
		printf("minishell error : command not found\n");
		exit(127);
	}
	else if (!(ft_strncmp(com->argv[0], "./", 2)))
	{
		return (ft_strdup(com->argv[0]));
	}
	path = for_access(com->argv[0], environ);
	if (!path && !(ft_strncmp(com->argv[0], "./", 2)))
	{
		printf("minishell error : command not found\n");
		destroy_com(com);
		free_env(environ);
		exit(1);
	}
	else if ((ft_strncmp(com->argv[0], "./", 2)))
		return (path);
	return (path);
}

void	child_process(t_command *first_com, t_command *command, int *tube, int fd)
{
	char	*path;
	char	**envi;

	envi = join_envi(command->envi);
	if (is_builtin_fork(command))
		exit(ft_builtins_fork(command, tube, envi));
	path = invalid_file(command, envi);
	is_access(path, command, envi);
	fd = redi_type(command, tube, fd);
	duping(fd, tube);
	execve(path, command->argv, envi);
	destroy_env(command->envi);
	if (path)
		free(path);
	destroy_com(first_com);
	free_env(envi);
	write(2, "minishell erreur : commande introuvable\n", 40);
	exit(127);
}

void	exec_command1(t_command *commands, int fd)
{
	int		tube[2];
	int		nbr;
	t_command	*first_com;

	first_com = commands;
	nbr = 0;
	while (commands)
	{
		if (commands->next)
			pipe(tube);
		else
			tube[1] = STDOUT_FILENO;
		commands->pid = fork();
		if (commands->pid == 0)
			child_process(first_com, commands, tube, fd);
		if (nbr++ > 0)
			close(fd);
		fd = tube[0];
		if (commands->next)
			close(tube[1]);
		commands = commands->next;
	}
}

int	exec_command(t_command *commands)
{
	int		exit_status;
	int		i;

	if (commands && !commands->next)
	{
		if (is_builtin(commands))
		{
			i = ft_builtins(commands);
			destroy_com(commands);
			return (i);
		}
	}
	exec_command1(commands, STDIN_FILENO);
	exit_status = wait_process(commands);
	destroy_com(commands);
	return (exit_status);
}
