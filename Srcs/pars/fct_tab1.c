/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:16 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/17 18:30:39 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	venv(char *str, int i, t_command *com, t_word *first)
{
	int		start;
	char	*name;
	char	*ret;

	start = ++i;
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_')))
			i++;
	name = ft_substr(str, start, (i - start));
	if (!name)
		return (-1);
	if (start == i && str[start] == '?' && ++i)
		ret = ft_itoa(com->exit_status);
	else if (start == i && (!str[i] || str[i] == ' ' || str[i] == '.'
			|| str[i] == '^'))
		ret = ft_strdup("$");
	else
		ret = ft_strdup(src_envi(name, com->envi));
	if (!ret)
		ret = ft_strdup("");
	place_word(first, ret);
	free(name);
	return (i);
}

int	squotes(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	start = ++i;
	end = i;
	while (str[end] && str[end] != '\'')
		end++;
	if (start == end)
		place_word(first, ft_strdup(""));
	else
		place_word(first, cut_word(str, start, end));
	(void)com;
	return (++end);
}

int	dquotes(char *str, int i, t_command *com, t_word *first)
{
	t_word	*new;
	int		(*fct_tab[128])(char *str, int i, t_command *com, t_word *first);
	int		n;

	n = 0;
	i++;
	while (n < 128)
		fct_tab[n++] = alpha_num_quotes;
	fct_tab['$'] = venv;
	new = malloc(sizeof(t_word));
	if (!new)
		return (-12);
	new->next = NULL;
	new->cont = NULL;
	n = i;
	while (str[i] && str[i] != '\"')
		i = fct_tab[(int)str[i]](str, i, com, new);
	if (n == i)
	{
		free(new);
		place_word(first, ft_strdup(""));
	}
	else
		place_word(first, lch_to_str(new));
	return (++i);
}

int	word(char *str, int i, t_command *com, t_word *first)
{
	t_word	*new;
	int		(*fct_tab[256])(char *str, int i, t_command *com, t_word *first);
	int		n;

	n = 0;
	while (n < 256)
		fct_tab[n++] = alpha_num;
	fct_tab['\"'] = dquotes;
	fct_tab['\''] = squotes;
	fct_tab['\\'] = back_slash;
	fct_tab['$'] = venv;
	new = malloc(sizeof(t_word));
	if (!new)
		return (-12);
	new->next = NULL;
	new->cont = NULL;
	while (str[i] && str[i] != ' ')
		i = fct_tab[(int)str[i]](str, i, com, new);
	place_word(first, lch_to_str(new));
	return (i);
}

int	alpha_num_quotes(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	start = i;
	end = i;
	while (str[end] && str[end] != '\"' && str[end] != '$')
		end++;
	place_word(first, cut_word(str, start, end));
	(void)com;
	return (end);
}
