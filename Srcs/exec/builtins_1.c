#include "../minishell.h"

int	ft_pwd(int *tube)
{
	char	buffer[4096];

	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	getcwd(buffer, 4096);
	printf("%s\n", buffer);
	return (0);
}

int	ft_export(char *new_env, t_envi *envi)
{
	char	*name;

	if (!new_env)
	{
		export_no_arg(envi);
		return (0);
	}
	if (!ft_is_in(new_env, '='))
		return (0);
	name = var_name(new_env);
	ft_unset(name, envi);
	add_new(new_env, envi);
	free(name);
	return (0);
}

int	ft_unset(char *var_name, t_envi *envi)
{
	t_envi	*prev;
	t_envi	*next;
	t_envi	*par;

	par = envi;
	if (!var_name)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	if (ft_strcmp(par->name, var_name) == 0)
	{
		envi = par->next;
		free(par->name);
		free(par->path);
		free(par);
		return (0);
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
			return (0);
		}
	}
	return (0);
}

int	ft_env(int *tube, t_envi *envi, char *argv1)
{
	char	**env;
	int		i;

	i = 0;
	if (argv1)
	{
		printf ("%s\n", strerror(2));
		return (127);
	}
	env = join_envi(envi);
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	while (env[i])
	{
		printf("%s\n", env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}

int	ft_cd(char *path, t_command command)
{
	if (!path)
		path = src_envi("HOME", command.envi);
	if (chdir(path) == -1)
		printf("%s\n", strerror(errno));
	return (0);
}
