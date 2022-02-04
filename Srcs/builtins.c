/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:50:11 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/04 16:55:40 by maskedduck       ###   ########.fr       */
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
			*envi = tmp;
		}
		else
			envi = &(*envi)->next;
	}
}

void	ft_env(t_envi *envi)
{
	char **env;
	int i;

	i = 0;
	env = join_envi(envi);
	while (env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
}

int		echo_flag(char *flag)
{
	int i;

	i = 0;
	if (flag[i++] == '-')
	{
		while (flag[i])
		{
			if (flag[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **argv)
{
	int i;

	i = 2;
	if (argv[1] && echo_flag(argv[1]) == 0)
		i = 1;
	while (argv[i])
	{
		printf("%s",argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (argv[1] && echo_flag(argv[1]) == 0)
		printf("\n");
	
}

void	ft_cd(char *path)
{
	if (chdir(path) == -1)
		printf("%s\n",strerror(errno));
}
