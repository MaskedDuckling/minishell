/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:53 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/16 15:20:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_argnum(t_command *commands, int *check)
{
	*check = 2;
	printf("minishell: exit: %s : argument numérique nécessaire\n",
		commands[0].argv[1]);
	destroy_com(commands);
	return (1);
}

int	ft_exit(t_command *commands, int *check)
{
	(void)check;
	if (!ft_strcmp(commands[0].argv[0], "exit"))
	{
		if (commands[0].argv[1] && commands[0].argv[2])
		{
			if (is_num(commands[0].argv[1]))
			{
				*check = -7;
				printf("minishell: exit: trop d'arguments\n");
			}
			else
				ft_exit_argnum(commands, check);
			return (0);
		}
		if (commands[0].argv[1]
			&& is_num(commands[0].argv[1]))
					*check = (ft_atoi_long(commands[0].argv[1]) % 255);
		else if (commands[0].argv[1])
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

	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	i = 1;
	if (echo_flag(argv[1]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (echo_flag(argv[1]) == 0)
		printf("\n");
	return (0);
}

int	ft_cd(char *path, t_command command)
{
	if (!path)
		path = src_envi("HOME", command.envi);
	if (chdir(path) == -1)
		printf("%s\n", strerror(errno));
	return (0);
}
