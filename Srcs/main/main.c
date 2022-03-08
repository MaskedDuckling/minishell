#include "../minishell.h"

int	ft_exit(t_command *commands)
{
	if (!ft_strcmp(commands[0].argv[0], "exit"))
	{
		destroy_com(commands);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **environ)
{
	char		*line;
	t_command	*commands;
	int			check;
	t_envi		*envi;

	(void)ac;
	(void)av;
	envi = environnement(environ);
	if (sig_init())
		return (1);
	line = readline("minishell : ");
	check = 0;
	while (check >= 0 && line)
	{
		add_history(line);
		check = parsing(line, &commands, envi, check);
		if ((check > 0 && !commands)
			|| (check > 0 && (commands[0].argv[0]
			&& ft_exit(commands))))
			break ;
		check = erroring(check);
		if (check > 0)
			check = exec_command(commands);
		else
			destroy_com(commands);
		free(line);
		line = readline("minishell : ");
	}
	free(line);
	destroy_env(envi);
}
