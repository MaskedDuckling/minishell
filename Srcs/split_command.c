/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:36:10 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/02 17:34:59 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char **make_argv(t_word *first)
{
	int	i;
	int	j;
	t_word	*tmp;
	char	**argv;

	tmp = first;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * i);
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

int		parse_command(char *str, t_command *com, int (*fct_tab[128])(char *str, int i,
		t_command *com, t_word *first))
{
	int		i;
	t_word	*first;

 	i = 0;
	first = malloc(sizeof(t_word));
	if (!first)
		return(-1);
	first->cont = NULL;
	first->next = NULL;
	while (i < ft_strlen(str))
		i = fct_tab[(int)str[i]](str, i, com, first);
	com->argv = make_argv(first);
	i = 0;
	while (com->argv[i])
		printf("%s\n", com->argv[i++]);
	return(1);
}

void	split_command(char **tab)
{
	int         i;
	int         size_tab;
	t_command   *command;
	int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first);
		
	size_tab = len_tab(tab);
	command = malloc(sizeof(t_command) * size_tab);
	if (!command)
		return ;
	init_fct_tab(fct_tab);
	i = 0;
	while (i >= 0 && i < size_tab)
	{
		parse_command(tab[i], &command[i], fct_tab);
		i++;
	}
}
