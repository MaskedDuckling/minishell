#include "minishell.h"

int  len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char **make_argv(t_word *first)
{
	int	i;
	int	j;
	t_word	*tmp;
	char	**argv;

	tmp = first;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (NULL);
	j = 0;
	while (j < i)
	{
		argv[j++] = first->cont;
		first = first->next;
	}
	argv[j] = NULL;
	return (argv);
}

void	destroy_word(t_word	*first)
{
	t_word	*tmp;

	while (first)
	{
		tmp = first->next;
		free(first);
		first = tmp;
	}
}
int		parse_command(char *str, t_command *com, int (*fct_tab[128])(char *str, int i,
		t_command *com, t_word *first), t_envi *envi)
{
	int		i;
	t_word	*first;

 	i = 0;
	first = malloc(sizeof(t_word));
	if (!first)
		return(-1);
	first->cont = NULL;
	first->next = NULL;
	
	com->envi = envi;
	while (i >= 0 && i < ft_strlen(str))
		i = fct_tab[(int)str[i]](str, i, com, first);
	if (i >= 0)
		com->argv = make_argv(first->next);
	destroy_word(first);
	t_redi *tmp;
	tmp = com->redi;
	while (tmp)
	{
		printf("redi type %i cont: |%s|\n", tmp->type, tmp->cont);
		tmp = tmp->next;
	}
	i = 0;
	while (com->argv[i])
		printf("|%s|\n", com->argv[i++]);


	return(i);
}

int			split_command(char **tab, t_envi *envi, t_command **com)
{
	int         i;
	int         size_tab;
	t_command   *command;
	int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first);
	int		check;
		
	size_tab = len_tab(tab);
	command = malloc(sizeof(t_command) * (size_tab + 1));
	if (!command)
		return (-1);
	init_fct_tab(fct_tab);
	i = 0;
	check = 0;
	while (check >= 0 && i < size_tab)
	{
		command[i].redi = NULL;
		check = parse_command(tab[i], &command[i], fct_tab, envi);
		i++;
	}
	command[i].argv = NULL;
	*com = command;
	return(check);
}
