#include "pars.h"

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

int	venv(char *str, int i, t_command *com, t_word *first)
{
	int		start;
	char	*name;
	char	*ret;

	(void)str;
	(void)com;
	start = ++i;
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	name = ft_substr(str, start, (i - start));
	if (!name)
		return (-1);
	if (start == i)
		ret = ft_strdup("$");
	else if (start + 2 == i && str[i] == '?')
	{
		printf("OK\n");
		ret = ft_itoa(com->exit_status);
	}
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
	int		(*fct_tab[128])(char *str, int i, t_command *com, t_word *first);
	int		n;

	n = 0;
	while (n < 128)
		fct_tab[n++] = alpha_num;
	fct_tab['\"'] = dquotes;
	fct_tab['\''] = squotes;
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
