#include "minishell.h"

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
	if (ft_builtins(command) == 1)
		exit(1);
	environ = join_envi();
	path = for_access(command.argv[0], environ);
	execve(path, command.argv, environ);
	free_command(environ);
	free(path);
	free_process(command);
	exit(1);
}

void	exec_command(t_command *commands)
{
	int		tube[2];
	pid_t	pid;
	int		fd;
	int		i;

	i = 0;
	fd = STDIN_FILENO;
	while (commands[i].argv)
	{
		if (commands[i + 1].argv)
			pipe(tube);
		else
			tube[1] = STDOUT_FILENO;
		pid = fork();
		if (commands[i].redi && pid == 0)
			ft_redi(commands[i]);
		else if (pid == 0)
			child_process(commands[i], tube, fd);
		if (i > 0)
			close(fd);
		fd = tube[0];
		if (commands[i + 1].argv)
			close(tube[1]);
		i++;
	}
	while (i >= 0)
	{
		pid = waitpid(-1, 0, 0);
		i--;
	}
	destroy_com(commands);
}
