/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:01 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/20 01:50:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command(char **command)
{
	int	i;

	i = 1;
	free(command[0]);
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}

void	destroy_com(t_command *com)
{
	t_redi	*mem_redi;
	t_command	*mem_com;
	int	i;

	if (!com)
		return ;
	while (com)
	{
		i = 0;
		while (com->argv && com->argv[i])
			free(com->argv[i++]);
		if (com->argv)
			free(com->argv);
		while (com->redi)
		{
			mem_redi = com->redi;
			com->redi = com->redi->next;
			free(mem_redi->cont);
			free(mem_redi);
		}
		mem_com = com->next;
		free(com);
		com = mem_com;
	}
}

void	destroy_env(t_envi *envi)
{
	t_envi	*tmp;

	tmp = envi->next;
	free(envi);
	envi = tmp;
	while (envi)
	{
		tmp = envi;
		envi = envi->next;
		if (tmp)
		{
			if (tmp->path)
				free(tmp->path);
			if (tmp->name)
				free(tmp->name);
			free(tmp);
		}
	}
}

int	erroring(int check)
{
	if (check >= 0)
		return (check);
	else if (check != -7)
		printf("minishell ERROR : ");
	if (check == -12)
		printf("a malloc failed\n");
	else if (check == -2)
	{
		printf("parse error\n");
		g_is_running = 258;
	}
	else if (check == -8)
		printf("error line=NULL\n");
	else if (check == -9)
		printf("no envi\n");
	else if (check != -7)
		printf("unspecified error\n");
	if (check >= -10)
		return (0);
	return (check);
}
