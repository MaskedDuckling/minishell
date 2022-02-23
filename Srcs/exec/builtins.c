#include "exec.h"

int	ft_pwd(int *tube)
{
	char	buffer[4096];

	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	getcwd(buffer, 4096);
	printf("%s\n", buffer);
	return (1);
}

void	ft_export(char *new_env)
{
	add_new(new_env);
}

void	ft_unset(char *var_name)
{
	t_envi	*prev;
	t_envi	*next;
	t_envi	*par;

	par = glob.envi;
	if (ft_strcmp(par->name, var_name) == 0)
	{
		glob.envi = par->next;
		free(par->name);
		free(par->path);
		free(par);
		return ;
	}
	while (par->next)
	{
		prev = par;
		par = par->next;
		next = par->next;
		if (ft_strcmp(par->name, var_name) == 0)
		{
			free(par->name);
			free(par->path);
			free(par);
			prev->next = next;
			return ;
		}
	}
}

void	ft_env(int *tube)
{
	char	**env;
	int		i;

	i = 0;
	env = join_envi();
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	while (env[i])
	{
		printf("%s\n", env[i]);
		free(env[i]);
		i++;
	}
	free(env);
}

int	echo_flag(char *flag)
{
	int	i;

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

void	ft_echo(char **argv, int *tube)
{
	int	i;

	i = 2;
	if (argv[1] && echo_flag(argv[1]) == 0)
		i = 1;
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	while (argv[i])
	{
		printf("%s", argv[i]);
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
		printf("%s\n", strerror(errno));
}

int	ft_builtins(t_command command)
{
	if (ft_strcmp(command.argv[0], "export") == 0)
		ft_export(command.argv[1]);
	else if (ft_strcmp(command.argv[0], "unset") == 0)
		ft_unset(command.argv[1]);
	else if (ft_strcmp(command.argv[0], "cd") == 0)
		ft_cd(command.argv[1]);
	else
		return (0);
	free(command.argv[0]);
	free_process(command);
	return (1);
}

int	test_builtin(t_command command)
{
	if (ft_strcmp(command.argv[0], "export") == 0)
		return(1);
	if (ft_strcmp(command.argv[0], "unset") == 0)
		return(1);
	if (ft_strcmp(command.argv[0], "cd") == 0)
		return(1);
	return (0);

}

int	ft_builtins_fork(t_command command, int *tube)
{
	if (ft_strcmp(command.argv[0], "echo") == 0)
		ft_echo(command.argv, tube);
	else if (ft_strcmp(command.argv[0], "pwd") == 0)
		ft_pwd(tube);
	else if (ft_strcmp(command.argv[0], "env") == 0)
		ft_env(tube);
	else
		return (0);
	free(command.argv[0]);
	free_process(command);
	return (1);
}