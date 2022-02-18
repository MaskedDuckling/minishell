#include "minishell.h"

void	destroy(t_command *com)
{
	int	i;
	int j;
	t_redi *tmp_r;

	
	j = 0;
	while (com[j].argv)
	{
		printf("j = %i\n", j);
		i = 0;
		while (com[j].argv[i])
			free(com[j].argv[i++]);
		free(com[j].argv);
		while (com[j].redi)
		{
			tmp_r = com[j].redi;
			com->redi = com[j].redi->next;
			free(tmp_r);
		}
		j++;
	}
	free(com);
}

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	char *line;
	t_command	*commands;
	t_envi	*tmp;
	t_envi *envi;

	envi = environnement(environ);
	line = readline("minishell : ");
	while (line)
	{
		add_history(line);
		commands = parsing(line, envi);
		if (!commands || !ft_strcmp(commands[0].argv[0], "exit"))
			break;
		if (ft_strcmp(commands[0].argv[0], "cd") == 0)
			ft_cd(commands[0].argv[1]);
		exec_command(commands, &envi);
		free(line);
		line = readline("minishell : ");
		destroy(commands);
	}
	free(line);
	destroy(commands);

	while (envi)
	{
		tmp = envi;
		envi = envi->next;
		free(tmp->path);
		free(tmp->name);
		free(tmp);
	}
	write(1,"\n",1);
}