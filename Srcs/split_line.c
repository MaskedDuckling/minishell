/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:21:52 by maskedduck        #+#    #+#             */
/*   Updated: 2022/01/28 22:58:42 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *replace_newline(char *command, char c)
{
	int i = 0;
	int j = 1;

	while (command[i])
	{
		if (command[i] == c && j == 1)
			command[i] = '\n';
		if (command[i] == '"')
		{
			if (j == 0)
				j = 1;
			else
				j = 0;
		}
		i++;
	}
	return (command);
}

char    **split_line(char *command)
{
	char **ret = NULL;

	command = replace_newline(command, '|');
	ret = ft_split(command, '\n');
	return (ret);
}
