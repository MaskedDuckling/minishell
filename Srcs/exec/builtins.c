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
char	*var_name(char *def)
{
	char	*name;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (def[i] && def[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	while (y < i)
	{
		name[y] = def[y];
		y++;
	}
	name[i] = 0;
	return (name);
}

void	export_no_arg(t_envi *envi)
{
	t_envi *tmp;

	tmp = envi;
	while (tmp->next)
	{
		printf("declare -x %s=%s\n",tmp->name,tmp->path);
		tmp = tmp->next;
	}
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

int		ft_env(int *tube, t_envi *envi, char *argv1)
{
	char	**env;
	int		i;

	i = 0;
	if (argv1)
	{
		printf("%s\n",strerror(2));
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

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_atoi_long(char *str)
{
	long int nbr;
	int i;
	int sign;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == -1)
			nbr = nbr * 10 - (str[i] - 48);
		if (sign == 1)
			nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr);
}

int	ft_exit(t_command *commands, int *check)
{
	(void)check;
	if (!ft_strcmp(commands[0].argv[0], "exit"))
	{
		if (commands[0].argv[2])
		{
			*check = 2;
			destroy_com(commands);
			return (0);
		}
		if (commands[0].argv[1]
			&& is_num(commands[0].argv[1]))
				*check = (ft_atoi_long(commands[0].argv[1]) % 255);
		destroy_com(commands);
		return (1);
	}
	return (0);
}

int	echo_flag(char *flag)
{
	int	i;

	if (!flag)
		return (0);
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

int		ft_echo(char **argv, int *tube)
{
	int	i;

	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	i = 1;
	if (echo_flag(argv[1]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (echo_flag(argv[1]) == 0)
		printf("\n");
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

int	ft_builtins(t_command command)
{
	int	ret;
	if (ft_strcmp(command.argv[0], "export") == 0)
		ret = ft_export(command.argv[1], command.envi);
	else if (ft_strcmp(command.argv[0], "unset") == 0)
		ret = ft_unset(command.argv[1], command.envi);
	else if (ft_strcmp(command.argv[0], "cd") == 0)
		ret = ft_cd(command.argv[1], command);
	else
		return (0);
	free(command.argv[0]);
	free_process(command);
	return (ret);
}

int	is_builtin(t_command command)
{
	if ((ft_strcmp(command.argv[0], "export") == 0)
	|| (ft_strcmp(command.argv[0], "cd") == 0)
	|| (ft_strcmp(command.argv[0], "unset") == 0))
		return(1);
	return (0);

}
int	is_builtin_fork(t_command command)
{
	if ((ft_strcmp(command.argv[0], "echo") == 0)
	|| (ft_strcmp(command.argv[0], "pwd") == 0)
	|| (ft_strcmp(command.argv[0], "env") == 0))
		return (1);
	return(0);
}

int	ft_builtins_fork(t_command command, int *tube)
{
	int	ret;

	if (ft_strcmp(command.argv[0], "echo") == 0)
		ret = ft_echo(command.argv, tube);
	else if (ft_strcmp(command.argv[0], "pwd") == 0)
		ret = ft_pwd(tube);
	else if (ft_strcmp(command.argv[0], "env") == 0)
		ret = ft_env(tube, command.envi, command.argv[1]);
	else
		return (0);
	free(command.argv[0]);
	free_process(command);
	return (ret);
}