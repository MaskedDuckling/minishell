/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:48:16 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/01 18:33:50 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command command, int *tube)
{
	close(tube[1]);
	dup2(command.argv[2], STDIN_FILENO);
	dup2(tube[0], STDOUT_FILENO);
	close(tube[0]);
	execve(command.path_to_command, command.argv, command.environ);
}

void	parent_process(t_command command, int *tube)
{
	close(tube[0]);
	dup2(command.output, STDIN_FILENO);
	dup2(tube[1], STDIN_FILENO);
	close(tube[1]);
	execve(command.path_to_command, command.argv, command.environ);
}

void    exec_command(t_command *commands)
{
	int		tube[2];
	pid_t	pid;
	int i;

	i = 0;
	while (commands[i].path_to_command)
	{
		pipe(tube);
		pid = fork();
		if (pid == 0)
			child_process(commands[i], tube);
		else if (commands[i + 1].path_to_command)
			parent_process(commands[i + 1], tube);
		i++;
	}
}
