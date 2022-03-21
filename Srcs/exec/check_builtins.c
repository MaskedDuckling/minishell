/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:56 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/21 15:11:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_command *command)
{
	int	ret;
	int	i;

	i = 1;
	if (ft_strcmp(command->argv[0], "export") == 0)
		while (command->argv[i])
			ret = ft_export(command->argv[i++], command->envi);
	else if (ft_strcmp(command->argv[0], "unset") == 0)
		while (command->argv[i])
			ret = ft_unset(command->argv[i++], command->envi);
	else if (ft_strcmp(command->argv[0], "cd") == 0)
		ret = ft_cd(command->argv[1], command);
	else
		return (0);
	return (ret);
}

int	ft_builtins_fork(t_command *command, int *tube, char **envi)
{
	int	ret;

	if (ft_strcmp(command->argv[0], "echo") == 0)
		ret = ft_echo(command->argv, tube);
	else if (ft_strcmp(command->argv[0], "pwd") == 0)
		ret = ft_pwd(tube);
	else if (ft_strcmp(command->argv[0], "env") == 0)
		ret = ft_env(tube, command->envi, command->argv[1]);
	else
		return (0);
	free_env(envi);
	destroy_env(command->envi);
	destroy_com(command);
	return (ret);
}

int	is_builtin(t_command *command)
{
	if ((ft_strcmp(command->argv[0], "export") == 0)
		|| (ft_strcmp(command->argv[0], "cd") == 0)
		|| (ft_strcmp(command->argv[0], "unset") == 0))
		return (1);
	return (0);
}

int	is_builtin_fork(t_command *command)
{
	if ((ft_strcmp(command->argv[0], "echo") == 0)
		|| (ft_strcmp(command->argv[0], "pwd") == 0)
		|| (ft_strcmp(command->argv[0], "env") == 0))
		return (1);
	return (0);
}
