/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:19:22 by eestela           #+#    #+#             */
/*   Updated: 2022/03/21 14:21:33 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exp_heredoc(t_command *command, char *line, int i, int tube[2])
{
	t_word	*first;

	first = malloc(sizeof(t_word));
	first->cont = NULL;
	first->next = NULL;
	i = venv(line, i, command, first);
	write(tube[1], first->next->cont, ft_strlen(first->next->cont));
	destroy_word(first);
	if (i < 0)
		return (-1);
	return (i - 1);
}

int	type_four(t_command *command, int exp)
{
	char	*line;
	int		tube[2];
	int		i;

	pipe(tube);
	line = readline("> ");
	while (line && ft_strcmp(line, command->redi->cont))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$' && exp)
				i = exp_heredoc(command, line, i, tube);
			else
				write(tube[1], &line[i], 1);
			i++;
		}
		write(tube[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(tube[1]);
	return (tube[0]);
}

int	redi_type(t_command *command, int *tube, int fd)
{
	int		exp;
	t_redi	*tmp_r;

	while (command->redi)
	{
		exp = delimiter(command);
		if (command->redi->type == 2 || command->redi->type == 1)
			close (tube[1]);
		if (command->redi->type == 1)
			tube[1] = open(command->redi->cont, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else if (command->redi->type == 2)
			tube[1] = open(command->redi->cont, O_APPEND | O_WRONLY
					| O_CREAT, 0644);
		else if (command->redi->type == 3)
			fd = open(command->redi->cont, O_RDONLY | O_CREAT, 0644);
		else if (command->redi->type == 4)
			fd = type_four(command, exp);
		tmp_r = command->redi;
		command->redi = command->redi->next;
		free(tmp_r->cont);
		free(tmp_r);
	}
	return (fd);
}
