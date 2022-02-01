/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:36:10 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/01 20:41:33 by user42           ###   ########.fr       */
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
	{
		i = fct_tab[(int)str[i]](str, i, com, first);
	}
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
