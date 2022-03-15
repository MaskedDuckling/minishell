/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:27 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 18:03:03 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_sizenum(unsigned int n)
{
	if (n > 9)
		return (1 + ft_sizenum(n / 10));
	else
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char			*tab;
	int				len;
	unsigned int	m;
	int				plus;

	plus = 1;
	m = n;
	if (n < 0)
		m = -n;
	if (n < 0)
		plus++;
	len = ft_sizenum(m) + plus - 1;
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[len] = '\0';
	while (--len >= 0)
	{
		tab[len] = (m % 10) + '0';
		m = m / 10;
	}
	if (n < 0)
		tab[0] = '-';
	return (tab);
}

char	*cut_word(char *str, int start, int end)
{
	char	*ret;
	int		i;

	if (end - start <= 0)
		return (NULL);
	ret = malloc(sizeof(char) * (end - start + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	ret[i] = 0;
	return (ret);
}

int	place_word(t_word *first, char *ret)
{
	t_word	*new;

	if (!ret)
		return (-41);
	while (first && first->next)
		first = first->next;
	new = malloc(sizeof(t_word));
	if (!new)
		return (-12);
	new->cont = ret;
	new->next = NULL;
	first->next = new;
	return (0);
}

int	skip(char *str, int i, t_command *com, t_word *first)
{
	(void)first;
	(void)str;
	(void)com;
	return (i + 1);
}
