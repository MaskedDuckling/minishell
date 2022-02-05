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

	while (first->next)
		first = first->next;
	if (!first->cont)
	{
		first->cont = ret;
		return (0);
	}
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
	printf("skip\n");
	(void)first;
	(void)str;
	(void)com;
	i++;
	return(i);
}

int	alpha_num(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	printf("alpha_num\n");
	start = i;
	end = i;
	while (str[end] && str[end] != ' ' && str[end] != '\''
		&& str[end] != '"' && str[end] != '$')
		end++;
	place_word(first, cut_word(str, start, end));
	(void)com;
	return(end);
}

int	alpha_num_quotes(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	printf("alpha_num_quotes\n");
	start = i;
	end = i;
	while (str[end] && str[end] != '\''
		&& str[end] != '\"' && str[end] != '$')
		end++;
	place_word(first, cut_word(str, start, end));
	(void)com;
	return(end);
}

int	input(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	printf("input\n");
	start = ++i;
	while (str[start] && str[start] == ' ')
		start++;
	end = start;
	while (str[end] && str[end] != ' ')
		end++;
	com->input = cut_word(str, start, end);
	(void)first;
	return(end);
}

int	output(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	printf("output\n");
	start = ++i;
	while (str[start] && str[start] == ' ')
		start++;
	end = start;
	while (str[end] && str[end] != ' ')
		end++;
	com->output = cut_word(str, start, end);
	(void)first;
	return(end);
}



int	squotes(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	printf("squotes\n");
	start = ++i;
	end = i;
	while (str[end] && str[end] != '\'')
		end++;
	place_word(first, cut_word(str, start, end));
	(void)com;
	return(++end);
}

int	venv(char *str, int i, t_command *com, t_word *first)
{
	printf("venv\n");
	(void)first;
	(void)str;
	(void)com;
	while (str[i] && str[i] != ' ')
		i++;
	return(i);
}



char	*lch_to_str(t_word	*first)
{
	char *str;
	t_word	*tmp;

	tmp = first;
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

int	dquotes(char *str, int i, t_command *com, t_word *first)
{
	t_word	*new;
	int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first);
	int	n;

	n = 0;
	i++;
	while (n < 128)
		fct_tab[n++] = alpha_num_quotes;
	fct_tab['\''] = squotes;
	fct_tab['$'] = venv;
	new = malloc(sizeof(t_word));
	new->next = NULL;
	new->cont = NULL;
	while (str[i] && str[i] != '\"')
		i = fct_tab[(int)str[i]](str, i, com, new);
	place_word(first, lch_to_str(new));
	return (++i);
}

int		word(char *str, int i, t_command *com, t_word *first)
{
	t_word	*new;
	int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first);
	int	n;

	n = 0;
	while (n < 128)
		fct_tab[n++] = alpha_num;
	fct_tab['\"'] = dquotes;
	fct_tab['\''] = squotes;
	fct_tab['$'] = venv;
	new = malloc(sizeof(t_word));
	new->next = NULL;
	new->cont = NULL;
	while (str[i] && str[i] != ' ')
		i = fct_tab[(int)str[i]](str, i, com, new);
	place_word(first, lch_to_str(new));
	return (i);
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
