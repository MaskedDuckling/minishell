/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:31:54 by user42            #+#    #+#             */
/*   Updated: 2022/02/16 14:40:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_word(char *str, int start, int end)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (end - start + 1));
	if ((end - start < 1) || !ret)
		return(NULL);
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	ret[i] = 0;
	return(ret);
}

int	place_word(t_word *first, char *ret)
{
	t_word	*new;

	while (first && first->next)
		first = first->next;
	new = malloc(sizeof(t_word));
	if (!new)
		return (-1);
	new->cont = ret;
	new->next = NULL;
	first->next = new;
	return(0);
}

int	skip(char *str, int i, t_command *com, t_word *first)
{
	(void)first;
	(void)str;
	(void)com;
	i++;
	return(i);
}

char	*lch_to_str(t_word	*first)
{
	char *str;
	t_word	*tmp;

	tmp = first->next;
	if (!tmp->cont)
		return (NULL);
	str = tmp->cont;
	tmp = tmp->next;
	while (tmp)
	{
		str = ft_strjoin(str, tmp->cont);
		tmp = tmp->next;
	}
	return (str);
}

void	init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first))
{
	int	i;

	i = 0;
	while (i < 128)
		fct_tab[i++] = word;
	fct_tab[' '] = skip;
	fct_tab['<'] = input;
	fct_tab['>'] = output;
}

int		redi(t_command *com, char *cont, int type)
{
	t_redi	*tmp;
	t_redi	*mv;

	if (!cont || !type)
		return (-1);
	tmp = malloc(sizeof(t_redi));
	if (!tmp)
		return (-2);
	tmp->cont = cont;
	tmp->type = type;
	if (!com->redi)
	{
		com->redi = tmp;
		return (0);
	}
	mv = com->redi;
	while(mv->next)
		mv = mv->next;
	mv->next = tmp;
	return (0);
}