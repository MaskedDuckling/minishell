#include "../minishell.h"

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

void	destroy_com(t_command *com)
{
	int		i;
	int		j;
	t_redi	*tmp_r;

	j = 0;
	if (!com)
		return ;
	while (com[j].argv)
	{
		i = 0;
		if (com[j].argv)
		{
			while (com[j].argv[i])
			{
				free(com[j].argv[i++]);
			}
			free(com[j].argv);
		}
		while (com[j].redi)
		{
			tmp_r = com[j].redi;
			com[j].redi = com[j].redi->next;
			free(tmp_r->cont);
			free(tmp_r);
		}
		j++;
	}
	free(com[j].argv);
	free(com);
}

void	destroy_env(t_envi *envi)

{
	t_envi	*tmp;

	while (envi)
	{
		tmp = envi;
		envi = envi->next;
		free(tmp->path);
		free(tmp->name);
		free(tmp);
	}
}

void	erroring(int check)
{
	if (check >= 0)
		return ;
	
	printf("minishell ERROR : ");
	if (check == -12)
		printf("a malloc failed\n");
	else if (check == -2)
		printf("parse error\n");
	else if (check == -8)
		printf("error line=NULL\n");
	else
		printf("unspecified error\n");
}
