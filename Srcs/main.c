#include "minishell.h"

void	destroy_com(t_command *com)
{
	int	i;
	int j;
	t_redi *tmp_r;

	
	j = 0;
	if (!com)
		return ;
	while (com[j].argv)
	{
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
	printf("minishell error: ");
	if (check == -1)
		printf("a malloc failed\n");
	else if (check == -2)
		printf("parse error\n");
	else if (check == -3)
		printf("error line=NULL\n");
	else
		printf("unspecified error\n");

}

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	char *line;
	t_command	*commands;
	t_envi		*envi;
	int			check;

	envi = environnement(environ);
	line = readline("minishell : ");
	check = 0;
	while (line)
	{
		add_history(line);
		check = parsing(line, envi, &commands);
		if ((check > 0 && !commands)  
			|| (check > 0 && !ft_strcmp(commands[0].argv[0], "exit")))
			break;
		if (check > 0 && ft_strcmp(commands[0].argv[0], "cd") == 0)
			ft_cd(commands[0].argv[1]);
		if (check > 0)
			exec_command(commands, &envi);
		free(line);
		line = readline("minishell : ");
	}
	free(line);
	if (check > 0)
		destroy_com(commands);
	destroy_env(envi);
	write(1,"\n",1);
}