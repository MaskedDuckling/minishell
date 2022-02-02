/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:48:16 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/02 17:29:08 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command command, int *tube, int fd)
{
	close(tube[1]);
	if (fd != STDIN_FILENO)
		dup2(fd, STDIN_FILENO);
	if (tube[0] != STDOUT_FILENO)
		dup2(tube[0], STDOUT_FILENO);
	close(tube[0]);
	command.argv[0] = for_access(command.argv[0], command.environ);
	execve(command.argv[0], command.argv, command.environ);
}

void    exec_command(t_command *commands)
{
	int		tube[2];
	pid_t	pid;
	int		fd;
	int i;

	i = 0;
	fd = STDIN_FILENO;
	while (commands[i].argv)
	{
		pipe(tube);
		pid = fork();
		if (pid == 0)
			child_process(commands[i], tube, fd);
		fd = tube[1];
		i++;
	}
	close(tube[0]);
	close(tube[1]);
}

void	fake_main(int ac, char **av, char **environ)
{
	t_command *command = NULL;
	int i = 1;

	command = malloc(sizeof(t_command) * ac);
	if (!command)
		return ;
	while (i < ac)
	{
		av[i] = replace_newline(av[i], ' ');
		command[i - 1].argv = ft_split(av[i], '\n');
		command[i - 1].environ = environ;
		i++;
	}
	command[i - 1].argv = NULL;
	command[i - 1].environ = NULL;
	exec_command(command);
}