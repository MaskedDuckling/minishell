#include "minishell.h"

void	free_command(char **command)
{
	int	i;

	i = 1;
	free(command[0]);
	while (command[i] != 0)
	{
		free(command[i]);
		i++;
	}
	free(command);
}
