/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:09 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 20:51:19 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char *s1, char *s2)
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
	return (ret);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strend_is(char *str, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(str) - ft_strlen(end);
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] != end[j])
			return (0);
		j++;
	}
	return (1);
}
