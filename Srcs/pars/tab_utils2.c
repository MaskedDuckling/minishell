/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:40:30 by eydupray          #+#    #+#             */
/*   Updated: 2022/03/15 17:40:33 by eydupray         ###   ########.fr       */
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

void	init_fct_tab(int (*fct_tab[128])(char *str, int i,
		t_command *com, t_word *first))
{
	int	i;

	i = 0;
	while (i < 128)
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
