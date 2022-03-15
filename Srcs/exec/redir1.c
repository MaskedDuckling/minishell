/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:59 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 20:31:28 by eestela          ###   ########.fr       */
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
	int		end;
	int		start;
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

int	delimiter(t_command *command)
{
	int		i;
	t_word	*first;

	i = 0;
	while (command->redi->cont[i] && command->redi->cont[i] != '"'
		&& command->redi->cont[i] != '\'')
		i++;
	if (!command->redi->cont[i])
		return (1);
	first = malloc(sizeof(t_word));
	if (!first)
		return (-1);
	first->cont = NULL;
	first->next = NULL;
	i = word_delimiter(command->redi->cont, 0, command, first);
	free(command->redi->cont);
	command->redi->cont = first->next->cont;
	destroy_word(first);
	if (i < 0)
		return (-1);
	else
		return (0);
}
