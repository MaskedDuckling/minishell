#include "../minishell.h"



int	main(int ac, char **av, char **environ)
{
	char		*line;
	t_command	*commands;
	int			check;
	t_envi		*envi;

	(void)ac;
	(void)av;
	envi = environnement(environ);
	line = readline("minishell : ");
	check = 0;
	while (check >= -10)
	{
		//printf("line= %s\n", line);
		add_history(line);
		check = parsing(line, &commands, envi);
		if ((check > 0 && !commands)
			|| (check > 0 && (commands[0].argv[0]
			&& !ft_strcmp(commands[0].argv[0], "exit"))))
			break ;
		if (check > 0)
			exec_command(commands);
		free(line);
		erroring(check);
		line = readline("minishell : ");

	}
	free(line);
	if (check > 0)
		destroy_com(commands);
	destroy_env(envi);
}
