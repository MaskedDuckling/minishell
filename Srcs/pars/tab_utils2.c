/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:30 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/17 17:35:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*lch_to_str(t_word	*first)
{
	char	*str;
	t_word	*tmp;

	if (!first)
		return (NULL);
	tmp = first;
	first = first->next;
	free(tmp);
	str = first->cont;
	tmp = first->next;
	free(first);
	while (tmp && str)
	{
		str = ft_strjoin_free(str, tmp->cont);
		free(tmp->cont);
		first = tmp;
		tmp = tmp->next;
		free(first);
	}
	return (str);
}

void	init_fct_tab(int (*fct_tab[256])(char *str, int i,
		t_command *com, t_word *first))
{
	int	i;

	i = 0;
	while (i < 256)
		fct_tab[i++] = word;
	fct_tab[' '] = skip;
	fct_tab['<'] = input;
	fct_tab['>'] = output;
}

int	redi(t_command *com, char *cont, int type)
{
	t_redi	*tmp;
	t_redi	*mv;

	if (!cont || !type)
		return (-1);
	tmp = malloc(sizeof(t_redi));
	if (!tmp)
		return (-12);
	tmp->cont = cont;
	tmp->type = type;
	tmp->next = NULL;
	if (!com->redi)
	{
		com->redi = tmp;
		return (0);
	}
	mv = com->redi;
	while (mv->next)
		mv = mv->next;
	mv->next = tmp;
	return (0);
}

int	back_slash(char *str, int i, t_command *com, t_word *first)
{
	char	*new;

	(void)com;
	new = malloc(sizeof(char) * 2);
	if (!new)
		return (-12);
	if (str[i + 1])
	{
		new[0] = str[i + 1];
		new[1] = 0;
	}
	else
		new[0] = 0;
	place_word(first, new);
	if (str[i + 1])
		return (i + 2);
	return (i + 1);
}
