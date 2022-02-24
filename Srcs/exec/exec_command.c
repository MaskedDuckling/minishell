#include "exec.h"

void	free_process(t_command command)
{
	int	i;

	i = 1;
	while (command.argv[i])
		free(command.argv[i++]);
	free(command.argv);
}

void	child_process(t_command command, int *tube, int fd)
{
	char	*path;
	char	**environ;

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
	if (ft_builtins_fork(command, tube))
		exit(1);
	environ = join_envi(command.envi);
	path = for_access(command.argv[0], environ);
	execve(path, command.argv, environ);
	free_command(environ);
	destroy_env(command.envi);
	free(path);
	free_process(command);
	exit(1);
}

int	wait_process(t_command *command)
{
	int		status;
	size_t	i;

	status = 0;
	i = 0;
	while(command[i].argv)
	{
		if (!test_builtin(command[i]))
		{
			if (waitpid(command[i].pid, &status, 0) == -1)
				write(STDERR_FILENO, "ERROR\n", 6);
			if(WIFEXITED(status))
				command[i].exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				command[i].exit_status = WTERMSIG(status) + 128;
		}
		i++;
	}
	if (command[i - 1].exit_status == 131)
		write(1, "^\\Quit (core dumped)\n", 21);
	return (command[i - 1].exit_status);
}

int		exec_command(t_command *commands)
{
	int		tube[2];
	int		exit_status;
	int		fd;
	int		i;

	i = 0;
	fd = STDIN_FILENO;
	if (!commands[1].argv)
	{
		if (ft_builtins(commands[0]))
		{
			free(commands);
			return (0);
		}
	}
	while (commands[i].argv)
	{
		if (commands[i + 1].argv)
			pipe(tube);
		else
			tube[1] = STDOUT_FILENO;
		commands[i].pid = fork();
		if (commands[i].redi && commands[i].pid == 0)
			ft_redi(commands[i]);
		else if (commands[i].pid == 0)
			child_process(commands[i], tube, fd);
		if (i > 0)
			close(fd);
		fd = tube[0];
		if (commands[i + 1].argv)
			close(tube[1]);
		i++;
	}
	exit_status = wait_process(commands);
	destroy_com(commands);
	return (exit_status);
}
