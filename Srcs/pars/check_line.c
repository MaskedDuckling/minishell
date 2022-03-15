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

int	simple(char *str, int i)
{
	int	y;

	if (str[i + 1])
	{
		if (str[i] == str[i + 1])
			return (-2);
	}
	y = i;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (-2);
	return (y + 1);
}

int	simp_doub(char *str, int i)
{
	if ((str[i + 1] && str[i + 2])
		&& (str[i] == str[i + 1] && str[i] == str[i + 2]))
			return (-2);
	/*if (str[i + 1] && str[i] == str[i + 1])
	{
		if (str[i + 2] && str[i] == str[i + 2])
			return (i + 3);
		return (i + 2);
	}
	*/
	if (str[i + 1] && str[i] == str[i + 1])
		i++;
	if (no_arg_redi(str, ++i))
		return (-2);
	return (i);
}

void	init_tab(int (*tab[128])(char *str, int i))
{
	int	i;

	i = 0;
	while (i < 128)
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
	int	(*tab[128])(char *line, int i);

	init_tab(tab);
	if (!line)
		return (-8);
	i = 0;
	while (i >= 0 && line[i])
		i = tab[(int)line[i]](line, i);
	return (i);
}
