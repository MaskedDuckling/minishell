/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:12 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/17 16:21:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_c(char *str, int i)
{
	(void)str;
	return (i + 1);
}

int	no_arg_redi(char *str, int i)
{
	while (str[i] == ' ')
	{
		i++;
	}
	if (!str[i] || str[i] == '<' || str[i] == '>' || str[i] == '|')
		return (1);
	return (0);
}

int	open_close(char *str, int i)
{
	char	c;

	c = str[i];
	while (str[++i])
	{
		if (str[i] == c)
			return (i + 1);
	}
	return (-2);
}

void	init_tab(int (*tab[256])(char *str, int i))
{
	int	i;

	i = 0;
	while (i < 256)
		tab[i++] = skip_c;
	tab['"'] = open_close;
	tab['\''] = open_close;
	tab['|'] = simple;
	tab['<'] = simp_doub;
	tab['>'] = simp_doub;
}

int	check_line(char *line)
{
	int	i;
	int	(*tab[256])(char *line, int i);

	init_tab(tab);
	if (!line)
		return (-8);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && line[i] == '|')
		return (-2);
	while (i >= 0 && line[i])
		i = tab[(int)line[i]](line, i);
	return (i);
}
