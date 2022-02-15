#include "minishell.h"

t_command *parsing(char *line, t_envi *envi)
{
	char	**com;

	com = split_line(line);
	if (com)
		return (split_command(com, envi));
	return (NULL);
}
