/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:35 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 20:36:21 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	envi_len(t_envi *envi)
{
	int	i;

	i = 0;
	envi = envi->next;
	while (envi)
	{
		envi = envi->next;
		i++;
	}
	return (i);
}

char	**join_envi(t_envi *envi)
{
	char	**ret;
	int		i;
	int		j;
	t_envi	*tmp;

	j = 0;
	tmp = envi->next;
	i = envi_len(tmp);
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	while (j < i)
	{
		ret[j] = ft_strjoin(tmp->name, "=");
		ret[j] = ft_strjoin_free(ret[j], tmp->path);
		tmp = tmp->next;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

char	*src_envi(char *var_name, t_envi *envi)
{
	t_envi	*tmp;

	tmp = envi->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var_name) == 0)
			return (tmp->path);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_new(char *data, t_envi *envi)
{
	t_envi	*tmp;
	t_envi	*new;

	tmp = envi;
	while (tmp->next)
		tmp = tmp->next;
	new = malloc(sizeof(t_envi));
	new->path = ft_strdup(tochar(data, '='));
	new->name = ft_strdup(data);
	new->next = NULL;
	tmp->next = new;
}

t_envi	*environnement(char **environnement)
{
	int		i;
	t_envi	*envi;

	i = 0;
	if (!environnement || !environnement[0])
	{
		return (NULL);
	}
	envi = malloc(sizeof(t_envi));
	envi->path = NULL;
	envi->name = NULL;
	envi->next = NULL;
	while (environnement[i])
	{
		add_new(environnement[i], envi);
		i++;
	}
	return (envi);
}
