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
	if (sig_init())
		return (1);
	is_running = 0;
	line = readline("minishell : ");
	check = 0;
	while (check >= 0 && line)
	{
		is_running = 1;
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
		//printf("status = %i\n", check);
		is_running = 0;
		line = readline("minishell : ");
	}
	if (!line)
		printf("exit\n");
	free(line);
	destroy_env(envi);
}
