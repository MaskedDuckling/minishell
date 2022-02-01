/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:48:16 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/01 20:41:08 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command command, int *tube, int fd)
{
	close(tube[1]);
	if (!fd)
		dup2(command.argv[2], STDIN_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	dup2(tube[0], STDOUT_FILENO);
	close(tube[0]);
	command.path_to_command = for_access(command.path_to_command, command.environ);
	execve(command.path_to_command, command.argv, command.environ);
}

void    exec_command(t_command *commands)
{
	int		tube[2];
	pid_t	pid;
	int		fd;
	int i;

	i = 0;
	while (commands[i].path_to_command)
	{
		if (commands[i + 1].path_to_command)
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
