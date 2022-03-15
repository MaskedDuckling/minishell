/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:23 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 17:40:25 by eydupray         ###   ########.fr       */
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
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
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
				int (*fct_tab[128])(char *str, int i,
				t_command *com, t_word *first))
{
	int		i;
	t_word	*first;
	t_redi	*tmp;

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
	tmp = com->redi;
	return (i);
}

int	split_command(char **tab, t_command **com, t_envi *envi, int exit_status)
{
	int			i;
	int			size_tab;
	t_command	*command;
	int			(*fct_tab[128])(char *str, int i, t_command *com,
			t_word *first);
	int			check;

	size_tab = len_tab(tab);
	command = malloc(sizeof(t_command) * (size_tab + 1));
	if (!command)
		return (-12);
	init_fct_tab(fct_tab);
	i = 0;
	check = 0;
	while (check >= 0 && i < size_tab)
	{
		command[i].envi = envi;
		command[i].redi = NULL;
		command[i].argv = NULL;
		command[i].exit_status = exit_status;
		check = parse_command(tab[i], &command[i], fct_tab);
		i++;
	}
	command[i].argv = NULL;
	*com = command;
	return (check);
}
