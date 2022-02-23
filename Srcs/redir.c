#include "minishell.h"

int	type_four(t_command command)
{
	char	*line;
	int		fd;

	fd = open(command.redi->cont, O_CREAT | O_WRONLY, 0644);
	line = readline("> ");
	while (ft_strcmp(line, command.redi->cont))
	{
		write(fd, line, ft_strlen(line));
		line = readline("> ");
	}
	return (fd);
}

void	ft_redi(t_command command)
{
	char	*path;
	int		type;
	int		stin;
	int		stout;

	type = 0;
	path = NULL;
	stin = STDIN_FILENO;
	stout = STDOUT_FILENO;
	while (command.redi)
	{
		if (command.redi->type == 1)
			stout = open(command.redi->cont, O_WRONLY | O_CREAT, 0644);
		else if (command.redi->type == 2)
			stout = open(command.redi->cont, O_APPEND | O_WRONLY | O_CREAT, 0644);
		else if (command.redi->type == 3)
			stin = open(command.redi->cont, O_RDONLY | O_CREAT, 0644);
		else if (command.redi->type == 4)
			stin = type_four(command);
		if (!command.redi->next)
			break ;
		command.redi = command.redi->next;
	}
	path = for_access(command.argv[0], join_envi());
	dup2(stin, STDIN_FILENO);
	dup2(stout, STDOUT_FILENO);
	execve(path, command.argv, join_envi());
	exit(1);
}
