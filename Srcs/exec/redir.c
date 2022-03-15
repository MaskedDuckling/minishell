/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:59 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 17:40:00 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(char *line, int j)
{
	int	i;

	i = j;
	while (line[i] && ((line[i] >= '0' && line[i] <= '9')
			|| (line[i] >= 'a' && line[i] <= 'z')
			|| (line[i] >= 'A' && line[i] <= 'Z')
			|| (line[i] == '_')))
		i++;
	return (i - j);
}

int	quotes_delimiter(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;
	char	quotes;

	quotes = str[i];
	start = ++i;
	end = i;
	while (str[end] && str[end] != quotes)
		end++;
	if (start == end)
		place_word(first, ft_strdup(""));
	else
		place_word(first, cut_word(str, start, end));
	(void)com;
	return (++end);
}

int	alpha_num_delimiter(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	start = i;
	end = i;
	while (str[end] && str[end] != ' ' && str[end] != '\''
		&& str[end] != '"')
		end++;
	place_word(first, cut_word(str, start, end));
	(void)com;
	return (end);
}

int	word_delimiter(char *str, int i, t_command *com, t_word *first)
{
	t_word	*new;
	int		(*fct_tab[128])(char *str, int i, t_command *com, t_word *first);
	int		n;

	n = 0;
	while (n < 128)
		fct_tab[n++] = alpha_num;
	fct_tab['\"'] = quotes_delimiter;
	fct_tab['\''] = quotes_delimiter;
	new = malloc(sizeof(t_word));
	if (!new)
		return (-12);
	new->next = NULL;
	new->cont = NULL;
	while (str[i] && str[i] != ' ')
		i = fct_tab[(int)str[i]](str, i, com, new);
	place_word(first, lch_to_str(new));
	return (i);
}

void	init_fct_tab_delimiter(int		(*fct_tab[128])(char *str, int i, t_command *com, t_word *first))
{
	int	i;
	
	i = 0;
	while (i < 128)
		fct_tab[i++] = word;
}


int	delimiter(t_command *command)
{
	int	i;
	t_word	*first;

	i = 0;
	while (command->redi->cont[i] && command->redi->cont[i] == '"' && command->redi->cont[i] == '\'')
		i++;
	if (!command->redi->cont[i])
		return (1);
	first = malloc(sizeof(t_word));
	if (!first)
		return (-1);
	first->cont = NULL;
	first->next = NULL;
	i = word_delimiter(command->redi->cont, 0, command, first);
	printf("cont = |%s|\n", command->redi->cont);
	free(command->redi->cont);
	command->redi->cont = first->next->cont;
	destroy_word(first);
	printf("cont exp = |%s|\n", command->redi->cont);
	if (i < 0)
		return (-1);
	else
		return (0);
}

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
	char	*name;
	char	*path;

	pipe(tube);
	line = readline("> ");
	while (ft_strcmp(line, command.redi->cont))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$' && !exp)
				exp_heredoc(command, line, i, tube);
			else
				write(tube[1], &line[i], 1);
			i++;
		}
		write(tube[1], "\n", 1);
		line = readline("> ");
	}
	close(tube[1]);
	return (tube[0]);
}

void	ft_redi(t_command command)
{
	char	*path;
	int		type;
	int		stin;
	int		stout;
	char	**envi;
	int		exp;

	type = 0;
	path = NULL;
	stin = STDIN_FILENO;
	stout = STDOUT_FILENO;
	exp = delimiter(&command);
	while (command.redi)
	{
		if (command.redi->type == 1)
			stout = open(command.redi->cont, O_WRONLY | O_CREAT, 0644);
		else if (command.redi->type == 2)
			stout = open(command.redi->cont, O_APPEND | O_WRONLY
					| O_CREAT, 0644);
		else if (command.redi->type == 3)
			stin = open(command.redi->cont, O_RDONLY | O_CREAT, 0644);
		else if (command.redi->type == 4)
			stin = type_four(command, exp);
		if (!command.redi->next)
			break ;
		command.redi = command.redi->next;
	}
	envi = join_envi(command.envi);
	if (command.argv[0])
	{
		path = for_access(command.argv[0], envi);
		dup2(stin, STDIN_FILENO);
		dup2(stout, STDOUT_FILENO);
		execve(path, command.argv, envi);
		free_process(command);
		write(2, "minishell erreur : commande introuvable\n", 40);
	}
	destroy_env(command.envi);
	free_command(envi);
	free(path);
	exit(127);
}
