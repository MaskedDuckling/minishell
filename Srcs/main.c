#include "minishell.h"

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

int	main(int ac, char **av, char **environ)
{
	char		*line;
	t_command	*commands;
	int			check;

	(void)ac;
	(void)av;
	environnement(environ);
	line = readline("minishell : ");
	check = 0;
	while (line)
	{
		add_history(line);
		check = parsing(line, &commands);
		if ((check > 0 && !commands)
			|| (check > 0 && (commands[0].argv[0]
			&& !ft_strcmp(commands[0].argv[0], "exit"))))
			break ;
<<<<<<< HEAD
		//printf("check = %i\n", check);
		if (check > 0 && ( commands[0].argv[0]
			&& ft_strcmp(commands[0].argv[0], "cd") == 0))
			ft_cd(commands[0].argv[1]);
		if (check > 0)
=======
		if (check > 0 && !ft_builtins(commands[0]))
>>>>>>> afb1661ff014b6e79a8ef8742b6ead188ef61cf3
			exec_command(commands);
		free(line);
		erroring(check);
		line = readline("minishell : ");
	}
	free(line);
	if (check > 0)
		destroy_com(commands);
	destroy_env(glob.envi);
}
