/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:23 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/20 01:51:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**make_argv(t_word *first)
{
	int		i;
	int		j;
	t_word	*tmp;
	char	**argv;

	tmp = first;
	i = 0;
	while (tmp && tmp->cont && ++i)
		tmp = tmp->next;
	argv = malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (NULL);
	j = 0;
	while (j < i)
	{
		argv[j++] = first->cont;
		first = first->next;
	}
	argv[j] = NULL;
	return (argv);
}

void	destroy_word(t_word	*first)
{
	t_word	*tmp;

	while (first)
	{
		tmp = first->next;
		free(first);
		first = tmp;
	}
}

int	parse_command(char *str, t_command *com,
				int (*fct_tab[256])(char *str, int i,
				t_command *com, t_word *first))
{
	int		i;
	t_word	*first;

	i = 0;
	first = malloc(sizeof(t_word));
	if (!first)
		return (-12);
	first->cont = NULL;
	first->next = NULL;
	while (i >= 0 && i < ft_strlen(str))
		i = fct_tab[(int)str[i]](str, i, com, first);
	if (i >= 0)
		com->argv = make_argv(first->next);
	destroy_word(first);
	return (i);
}	

int	init_commands(t_command **commands,int  size)
{
	t_command	*tmp;

	*commands = malloc(sizeof(t_command));
	if (!commands)
		return (-12);
	tmp = *commands;
	while (size-- - 1)
	{
		tmp->next = malloc(sizeof(t_command));
		if (!tmp->next)
			return (-12);
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (0);
}

int	split_command(char **tab, t_command **commands, t_envi *envi, int exit_status)
{
	int			i;
	int			size;
	t_command	*tmp_com;
	int			(*fct_tab[256])(char *str, int i, t_command *com,
			t_word *first);
	int			check;

	size = len_tab(tab);
	check = init_commands(commands, size);
	if (!*commands)
		return (-12);
	init_fct_tab(fct_tab);
	tmp_com = *commands;
	i = -1;
	while (check >= 0 && ++i < size)
	{
		tmp_com->envi = envi;
		tmp_com->redi = NULL;
		tmp_com->argv = NULL;
		tmp_com->exit_status = exit_status;
		check = parse_command(tab[i], tmp_com, fct_tab);
		tmp_com = tmp_com->next;
	}
	return (check);
}
