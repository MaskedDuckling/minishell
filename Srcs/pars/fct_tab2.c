/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:43:45 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/17 18:30:06 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	simple(char *str, int i)
{
	int	y;

	i = i + 1;
	if (str[i] && str[i - 1] == str[i])
		return (-2);
	y = i;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (-2);
	return (y);
}

int	simp_doub(char *str, int i)
{
	if ((str[i + 1] && str[i + 2])
		&& (str[i] == str[i + 1] && str[i] == str[i + 2]))
		return (-2);
	if (str[i + 1] && str[i] == str[i + 1])
		i++;
	if (no_arg_redi(str, ++i))
		return (-2);
	return (i);
}

int	alpha_num(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	start = i;
	end = i;
	while (str[end] && str[end] != ' ' && str[end] != '\''
		&& str[end] != '"' && str[end] != '$')
		end++;
	place_word(first, cut_word(str, start, end));
	(void)com;
	return (end);
}

int	input(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;
	int	type;

	type = 3;
	if (str[i + 1] && str[i + 1] == '<' && ++i)
		type++;
	start = ++i;
	while (str[start] && str[start] == ' ')
		start++;
	end = start;
	while (str[end] && str[end] != ' ')
		end++;
	redi(com, cut_word(str, start, end), type);
	(void)first;
	return (end);
}

int	output(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;
	int	type;

	type = 1;
	if (str[i + 1] && str[i + 1] == '>' && ++i)
		type++;
	start = ++i;
	while (str[start] && str[start] == ' ')
		start++;
	end = start;
	while (str[end] && str[end] != ' ')
		end++;
	redi(com, cut_word(str, start, end), type);
	(void)first;
	return (end);
}
