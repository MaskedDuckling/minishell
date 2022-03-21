/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:39:47 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/21 14:25:19 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t			s1len;
	size_t			s2len;
	unsigned int	i;
	unsigned int	j;
	char			*ret;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	i = -1;
	j = 0;
	ret = malloc(sizeof(char) * (s2len + s1len + 1));
	if (!ret)
		return (NULL);
	while (++i < s1len)
		ret[i] = s1[i];
	while (j < s2len)
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	free(s1);
	return (ret);
}

char	*for_for_access(char **path, char *join, int i, char *cmd)
{
	i = 0;
	if (!path)
		return (NULL);
	while (path[i] != 0)
	{
		if (ft_strend_is(path[i], "/") == 0)
			path[i] = ft_strjoin_free(path[i], "/");
		join = ft_strjoin(path[i], cmd);
		if (access(join, F_OK) == 0)
		{
			free_command(path);
			return (join);
		}
		free(join);
		i++;
	}
	free_command(path);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*for_access(char *cmd, char **environ)
{
	int			i;
	char		**path;
	char		*join;

	i = -1;
	path = NULL;
	join = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], "PATH=", 5))
		{
			path = ft_split(environ[i] + 5, ':');
			break ;
		}	
	}
	join = for_for_access(path, join, i, cmd);
	if (join)
		return (join);
	return (NULL);
}
