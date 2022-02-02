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
	while (str[end] && str[end] != ' ')
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

int	dquotes(char *str, int i, t_command *com, t_word *first)
{
	int	end;
	int	start;

	printf("dquotes\n");
	start = ++i;
	end = i;
	while (str[end] && str[end] != '\"')
		end++;
	place_word(first, cut_word(str, start, end));
	(void)com;
	return(++end);
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

void	init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first))
{
	int	i;

	i = 0;
	while (i < 128)
		fct_tab[i++] = skip;
	i = 'A';
	while (i <= 'Z')
		fct_tab[i++] = alpha_num;
	i = 'a';
	while (i <= 'z')
		fct_tab[i++] = alpha_num;
	 i = '0';
	while (i <= '9')
		fct_tab[i++] = alpha_num;
	fct_tab['<'] = input;
	fct_tab['>'] = output;
	fct_tab['\"'] = dquotes;
	fct_tab['\''] = squotes;
	fct_tab['$'] = venv;
}
