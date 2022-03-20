/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:19:22 by eestela           #+#    #+#             */
/*   Updated: 2022/03/19 20:40:43 by user42           ###   ########.fr       */
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

void	ft_redi(t_command *command, int fd, int *tube)
{
	char	*path;
	char	**envi;

	envi = join_envi(command->envi);
	path = invalid_file(command, envi);
	is_access(path, command, envi);
	fd = redi_type(command, tube, fd);
	if (command->argv[0])
	{
		if (fd != STDIN_FILENO)
			dup2(fd, STDIN_FILENO);
		if (tube[1] != STDOUT_FILENO)
			dup2(tube[1], STDOUT_FILENO);
		if (is_builtin_fork(command))
			exit(ft_builtins_fork(command, tube, envi));
		execve(path, command->argv, envi);
		free(command->argv[0]);
		free_process(command);
		write(2, "minishell erreur : commande introuvable\n", 40);
	}
	destroy_env(command->envi);
	free_command(envi);
	if (path)
		free(path);
	exit(127);
}
