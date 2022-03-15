/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:01 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 17:40:02 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_is_running;

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

int	destroy_com1(t_command *com, int j)
{
	int		i;
	t_redi	*tmp_r;

	while (com[j].argv)
	{
		i = 0;
		if (com[j].argv)
		{
			while (com[j].argv[i])
			{
				free(com[j].argv[i++]);
			}
			free(com[j].argv);
		}
		while (com[j].redi)
		{
			tmp_r = com[j].redi;
			com[j].redi = com[j].redi->next;
			free(tmp_r->cont);
			free(tmp_r);
		}
		j++;
	}
	return (j);
}

void	destroy_com(t_command *com)
{
	int		j;

	j = 0;
	if (!com)
		return ;
	j = destroy_com1(com, 0);
	free(com[j].argv);
	free(com);
}

void	destroy_env(t_envi *envi)

{
	t_envi	*tmp;

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
