/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:38:13 by eestela           #+#    #+#             */
/*   Updated: 2022/03/21 17:53:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	duping(int fd, int *tube)
{
	if (fd != STDIN_FILENO)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (tube[1] != STDOUT_FILENO)
	{
		dup2(tube[1], STDOUT_FILENO);
		close(tube[1]);
	}
}

int	wait_process(t_command *command)
{
	int		status;
	//size_t	i;
	t_command	*prev_com;

	status = 0;
	//i = 0;
	prev_com = NULL;
	while (command)
	{
		if (command->argv[0] && !is_builtin(command))
		{
			if (waitpid(command->pid, &status, 0) == -1)
				write(STDERR_FILENO, "ERROR\n", 6);
			if (WIFEXITED(status))
				command->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				command->exit_status = WTERMSIG(status) + 128;
		}
		prev_com = command;
		command = command->next;
	}
	if (prev_com && prev_com->exit_status == 131)
		write(1, "^\\Quit (core dumped)\n", 21);
	return (prev_com->exit_status);
}

void	is_access(char *path, t_command *command, char **environ)
{
	if (path && access(path, F_OK) == 0 && access(path, X_OK) == -1
		&& !(ft_strncmp(path, "./", 2)))
	{
		printf("minishell error : Permission denied\n");
		if (path)
			free(path);
		free(command->argv[0]);
		free_process(command);
		free_env(environ);
		exit(126);
	}
}
