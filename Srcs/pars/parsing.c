/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:20 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/20 01:19:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	parsing(char *line, t_command **command, t_envi *envi, int exit_status)
{
	char	**com;
	int		check;

	com = NULL;
	if (!envi)
		return (-9);
	check = check_line(line);
	if (check < 0)
		return (check);
	com = split_line(line);
	if (com && com[0])
		check = split_command(com, command, envi, exit_status);
	else if (!com || !com[0])
		check = -12;
	ft_free_tab(com);
	return (check);
}
