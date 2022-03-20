/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:04 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/19 22:50:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*new;
	int		i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		new[i++] = s[start++];
	if (start > ft_strlen(s))
		new[0] = 0;
	new[i] = 0;
	return (new);
}

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		i;
	int		len;

	len = 0;
	new = NULL;
	if (!s1)
		return (NULL);
	while (s1[len])
		len++;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	new[i] = '\0';
	return (new);
}

char	*ft_strndup(const char *s1, int n)
{
	char	*new;
	int		i;
	int		len;

	len = 0;
	new = NULL;
	if (!s1)
		return (NULL);
	while (s1[len] && len < n)
		len++;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i] && i < n)
		new[i] = s1[i];
	new[i] = '\0';
	return (new);
}

int	ft_is_in(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*tochar(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
		{
			s1[i] = '\0';
			return (s1 + i + 1);
		}
		i++;
	}
	return (NULL);
}
