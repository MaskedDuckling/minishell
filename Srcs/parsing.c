#include "minishell.h"

int		check_line(char *line)
{
	int	i;
	int	check;

	if (!line)
		return (-3);
	check = 0;
	i = 0;
	while (line[i])
	{
		break ;
	}
	return (check);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
int		parsing(char *line, t_envi *envi, t_command **command)
{
	char	**com;
	int		check;

	check = check_line(line);
	if (check < 0)
		return (check);
	com = NULL;
	com = split_line(line);
	if (com && com[0])
		check = split_command(com, envi, command);
	else if (!com || !com[0])
		check = 0;
	ft_free_tab(com);
	return (check);
}
