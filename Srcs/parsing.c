/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:09:19 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/01 16:50:38 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *parsing(char *line, char **environ)
{
	char	**com;

	environ = NULL;
	com = split_line(line);
	split_command(com);
	return (NULL);
}
