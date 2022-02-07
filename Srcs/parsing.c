/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:09:19 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/07 15:08:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *parsing(char *line, char **environ)
{
	char	**com;

	environ = NULL;
	com = split_line(line);
	return (split_command(com));
}
