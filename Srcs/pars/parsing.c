#include "pars.h"

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

int	parsing(char *line, t_command **command, t_envi *envi)
{
	char	**com;
	int		check;

	com = NULL;
	check = check_line(line);
	if (check < 0)
		return (check);
	com = split_line(line);
	if (com && com[0])
		check = split_command(com, command, envi);
	else if (!com || !com[0])
		check = 0;
	ft_free_tab(com);
	return (check);
}
