/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:03 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/20 01:52:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_is_running;

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i++] != ' ')
			return (0);
	}
	return (1);
}

int	routine(int check, t_command *commands, t_envi *envi, char **line)
{
	while (check >= 0 && *line)
	{
		commands = NULL;
		if (is_empty(*line))
		{
			free(*line);
			*line = ft_strdup("");
		}
		g_is_running = 1;
		add_history(*line);
		check = parsing(*line, &commands, envi, check);
		if (((check > 0 && !commands))
			|| (check > 0 && (commands->argv[0]
					&& ft_exit(commands, &check))))
			break ;
		check = erroring(check);
		if (check > 0)
			check = exec_command(commands);
		else
			destroy_com(commands);
		free(*line);
		g_is_running = 0;
		*line = readline("minishell : ");
	}
	return (check);
}

int	main(int ac, char **av, char **environ)
{
	char		*line;
	t_command	*commands;
	int			ret_value;
	t_envi		*envi;

	(void)av;
	g_is_running = 0;
	commands = NULL;
	envi = environnement(environ);
	if (!envi && ac > 0)
	{
		printf("minishell error : no env\n");
		exit(1);
	}
	if (sig_init())
		return (1);
	line = readline("minishell : ");
	ret_value = routine(0, commands, envi, &line);
	if (!line)
		printf("exit\n");
	destroy_env(envi);
	if (line)
		free(line);
	rl_clear_history();
	return (ret_value);
}
