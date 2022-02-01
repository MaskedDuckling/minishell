/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:40:20 by eydupray          #+#    #+#             */
/*   Updated: 2022/01/19 16:41:04 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(char **command)
{
	int	i;

	i = 1;
	free(command[0]);
	while (command[i] != 0)
	{
		free(command[i]);
		i++;
	}
	free(command);
}
