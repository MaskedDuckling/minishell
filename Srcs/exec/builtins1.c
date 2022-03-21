/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:51 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/21 14:48:31 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int *tube)
{
	char	buffer[4096];

	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	getcwd(buffer, 4096);
	printf("%s\n", buffer);
	return (0);
}

int	ft_export_check(char *s)
{
	int	i;

	i = 0;
	while((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
		i++;
	if (i == 0 || s[i] != '=')
		return (0);
	i++;
	while((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
		i++;
	if (!s[i])
		return (1);
	return (0);
}

int	ft_export(char *new_venv, t_envi *envi)
{
	char	*name;

	if (!new_venv)
	{
		export_no_arg(envi);
		return (0);
	}
	name = var_name(new_venv);
	if (!ft_export_check(new_venv) || !name)
	{
		printf("minishell error : export identifiant non valables\n");
		return (1);
	}
	ft_unset(name, envi);
	add_new(new_venv, envi);
	free(name);
	return (0);
}

int	for_ft_unset(char *var_name)
{
	if (!var_name)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	return (-1);
}

int	ft_unset(char *var_name, t_envi *envi)
{
	t_envi	*prev;
	t_envi	*next;
	t_envi	*par;
	int		ret;

	ret = for_ft_unset(var_name);
	if (ret >= 0)
		return (ret);
	par = envi->next;
	while (par->next)
	{
		prev = par;
		par = par->next;
		next = par->next;
		if (ft_strcmp(par->name, var_name) == 0)
		{
			free(par->name);
			free(par->path);
			free(par);
			prev->next = next;
			return (0);
		}
	}
	return (0);
}

int	ft_env(int *tube, t_envi *envi, char *argv1)
{
	char	**env;
	int		i;

	i = 0;
	if (argv1)
	{
		printf ("%s\n", strerror(2));
		return (127);
	}
	env = join_envi(envi);
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	while (env[i])
	{
		printf("%s\n", env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
