#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[4096];

	getcwd(buffer, 4096);
	printf("%s\n", buffer);
	return (1);
}

void	ft_export(t_envi **envi, char *new_env)
{
	add_new(envi, new_env);
}

void	ft_unset(t_envi **envi, char *var_name)
{
	t_envi *tmp;

	while (*envi)
	{
		tmp = (*envi)->next;
		if (ft_strcmp((*envi)->name, var_name) == 0)
		{
			free((*envi)->name);
			free((*envi)->path);
			free(*envi);
			*envi = tmp;
		}
		else
			envi = &(*envi)->next;
	}
}

void	ft_env(t_envi *envi)
{
	char **env;
	int i;

	i = 0;
	env = join_envi(envi);
	while (env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
	free(env);
}

int		echo_flag(char *flag)
{
	int i;

	i = 0;
	if (flag[i++] == '-')
	{
		while (flag[i])
		{
			if (flag[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **argv)
{
	int i;

	i = 2;
	if (argv[1] && echo_flag(argv[1]) == 0)
		i = 1;
	while (argv[i])
	{
		printf("%s",argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (argv[1] && echo_flag(argv[1]) == 0)
		printf("\n");
	
}

void	ft_cd(char *path)
{
	if (chdir(path) == -1)
		printf("%s\n",strerror(errno));
}



int	ft_builtins(t_command command, t_envi **envi)
{
	if (ft_strcmp(command.argv[0], "echo") == 0)
		ft_echo(command.argv);
	else if (ft_strcmp(command.argv[0], "export") == 0)
		ft_export(envi, command.argv[1]);
	else if (ft_strcmp(command.argv[0], "unset") == 0)
		ft_unset(envi, command.argv[1]);
	else if (ft_strcmp(command.argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command.argv[0], "env") == 0)
		ft_env(*envi);
	else
		return (0);
	free(command.argv[0]);
	free_process(command);
	return (1);
}