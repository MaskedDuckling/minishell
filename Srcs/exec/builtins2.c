/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:53 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/20 00:06:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_argnum(t_command *commands, int *check)
{
	*check = 2;
	printf("minishell: exit: %s : argument numérique nécessaire\n",
		commands->argv[1]);
	destroy_com(commands);
	return (1);
}

int	ft_exit(t_command *commands, int *check)
{
	if (!ft_strcmp(commands->argv[0], "exit"))
	{
		if (commands->argv[1] && commands->argv[2]
			&& is_num(commands->argv[1]))
		{
			*check = -7;
			printf("minishell: exit: trop d'arguments\n");
			return (0);
		}
		else if (commands->argv[1] && !is_num(commands->argv[1]))
		{
			ft_exit_argnum(commands, check);
			*check = 2;
			return (1);
		}
		if (commands->argv[1]
			&& is_num(commands->argv[1]))
					*check = (ft_atoi_long(commands->argv[1]) % 256);
		else if (commands->argv[1])
			*check = 2;
		destroy_com(commands);
		return (1);
	}
	return (0);
}

int	echo_flag(char *flag)
{
	int	i;

	if (!flag)
		return (0);
	i = 0;
	if (flag[i++] == '-')
	{
		while (flag[i])
		{
			if (flag[i] != 'n')
				return (0);
			i++;
		}
		if (i > 1)
			return (1);
	}
	return (0);
}

int	ft_echo(char **argv, int *tube)
{
	int	i;
	int	flag;

	if (tube[1] != STDOUT_FILENO)
	{
		close(tube[0]);
		dup2(tube[1], STDOUT_FILENO);
	}
	i = 1;
	flag = 0;
	while (echo_flag(argv[i]))
	{
		i++;
		flag = 1;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

int	ft_cd(char *path, t_command *command)
{
	if (!path)
		path = src_envi("HOME", command->envi);
	if (chdir(path) == -1)
		printf("%s\n", strerror(errno));
	return (0);
}
