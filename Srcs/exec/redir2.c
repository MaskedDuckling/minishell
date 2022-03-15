/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:19:22 by eestela           #+#    #+#             */
/*   Updated: 2022/03/15 20:26:42 by eestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exp_heredoc(t_command command, char *line, int i, int tube[2])
{
	t_word	*first;
	int		ret;

	first = malloc(sizeof(t_word));
	first->cont = NULL;
	first->next = NULL;
	ret = venv(line, i, &command, first);
	write(tube[1], first->next->cont, ft_strlen(first->next->cont));
	destroy_word(first);
	if (ret < 0)
		return (-1);
	return (i);
}

int	type_four(t_command command, int exp)
{
	char	*line;
	int		tube[2];
	int		i;

	pipe(tube);
	line = readline("> ");
	while (line && ft_strcmp(line, command.redi->cont))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$' && exp)
				exp_heredoc(command, line, i, tube);
			else
				write(tube[1], &line[i], 1);
			i++;
		}
		write(tube[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(tube[1]);
	return (tube[0]);
}

t_st	redi_type(t_command *command)
{
	int		type;
	int		exp;
	t_st	st;

	type = 0;
	st.in = STDIN_FILENO;
	st.out = STDOUT_FILENO;
	exp = delimiter(command);
	while (command->redi)
	{
		if (command->redi->type == 1)
			st.out = open(command->redi->cont, O_WRONLY | O_CREAT, 0644);
		else if (command->redi->type == 2)
			st.out = open(command->redi->cont, O_APPEND | O_WRONLY
					| O_CREAT, 0644);
		else if (command->redi->type == 3)
			st.in = open(command->redi->cont, O_RDONLY | O_CREAT, 0644);
		else if (command->redi->type == 4)
			st.in = type_four(*command, exp);
		if (!command->redi->next)
			break ;
		command->redi = command->redi->next;
	}
	return (st);
}

void	ft_redi(t_command command)
{
	char	*path;
	t_st	st;
	char	**envi;

	path = NULL;
	st = redi_type(&command);
	envi = join_envi(command.envi);
	if (command.argv[0])
	{
		path = for_access(command.argv[0], envi);
		dup2(st.in, STDIN_FILENO);
		dup2(st.out, STDOUT_FILENO);
		execve(path, command.argv, envi);
		free_process(command);
		write(2, "minishell erreur : commande introuvable\n", 40);
	}
	destroy_env(command.envi);
	free_command(envi);
	if (path)
		free(path);
	exit(127);
}
