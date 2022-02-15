#include "minishell.h"

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	char *line;
	t_command *commands;
	t_envi *envi;

	envi = environnement(environ);
	line = readline("minishell : ");
	while (line)
	{
		add_history(line);
		commands = parsing(line, envi);
		if (!commands || !ft_strcmp(commands[0].argv[0], "exit"))
			break;
		exec_command(commands, &envi);
		line = readline("minishell : ");
	}
	write(1,"\n",1);
}