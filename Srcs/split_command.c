/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:36:10 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/01 18:40:14 by maskedduck       ###   ########.fr       */
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
		t_command *com))
{
	int	i;
	
	i = 0;
	while (i < ft_strlen(str))
	{
		i = fct_tab[(int)str[i]](str, i, com);
	}
	return(1);
}

void	split_command(char **tab)
{
	int         i;
	int         size_tab;
	t_command   *command;
	int (*fct_tab[128])(char *str, int i, t_command *com);
	
	
	i = 0;
	size_tab = len_tab(tab);
	command = malloc(sizeof(t_command) * size_tab);
	if (!command)
		return ;
	init_fct_tab(fct_tab);
	while (i < size_tab)
	{
		parse_command(tab[i], &command[i], fct_tab);
		i++;
	}
}
