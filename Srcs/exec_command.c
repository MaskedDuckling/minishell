#include "minishell.h"

// cat Makefile | cat | wc

void	child_process(t_command command, int *tube, int fd)
{
	char	*path;

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
	path = for_access(command.argv[0], join_envi(command.envi));
	execve(path, command.argv, join_envi(command.envi));
	exit(1);
}

void	exec_command(t_command *commands)
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
		else
			tube[1] = STDOUT_FILENO;
		pid = fork();
		if (pid == 0)
			child_process(commands[i], tube, fd);
		if (i > 0)
			close(fd);
		fd = tube[0];
		if (commands[i + 1].argv)
			close(tube[1]);
		i++;
	}
	printf("a\n");
	while (i >= 0)
	{
		pid = waitpid(-1, 0, 0);
		i--;
	}
}
