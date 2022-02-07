/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:48:16 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/07 14:17:14 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command command, int *tube, int fd)
{
	close(tube[1]);
	(void)fd;
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
		if (commands[i + 1].argv)
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
