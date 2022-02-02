/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:50:11 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/02 19:24:24 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[4096];

	getcwd(buffer, 4096);
	printf("%s\n", buffer);
	return (1);
}

void	ft_export(t_envi **envi, char *new_env)
{
	add_new(envi, new_env);
}

void	ft_unset(t_envi **envi, char *var_name)
{
	t_envi *tmp;

	while (*envi)
	{
		tmp = (*envi)->next;
		if (ft_strcmp((*envi)->name, var_name) == 0)
		{
			free((*envi)->name);
			free((*envi)->path);
			free(*envi);
		}
		*envi = tmp;
	}
}