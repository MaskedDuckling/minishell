#include "minishell.h"

char	*tochar(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
		{
			s1[i] = '\0';
			return (s1 + i + 1);
		}
		i++;
	}
	return (NULL);
}

int	envi_len(t_envi *envi)
{
	int	i;

	i = 0;
	while (envi)
	{
		envi = envi->next;
		i++;
	}
	return (i);
}

char	**join_envi(void)
{
	char	**ret;
	int		i;
	int		j;
	t_envi *tmp;

	j = 0;
	tmp = glob.envi;
	i = envi_len(tmp);
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	while (j < i)
	{
		ret[j] = ft_strjoin(tmp->name, "=");
		ret[j] = ft_strjoin_free(ret[j], tmp->path);
		tmp = tmp->next;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

char	*src_envi(char *var_name)
{
	t_envi *tmp;

	tmp = glob.envi;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var_name) == 0)
			return (tmp->path);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_new(char *data)
{
	t_envi	*tmp;
	t_envi	*new;

	tmp = glob.envi;
	while (tmp->next)
		tmp = tmp->next;
	new = malloc(sizeof(t_envi));
	new->path = ft_strdup(tochar(data, '='));
	new->name = ft_strdup(data);
	new->next = NULL;
	tmp->next = new;
	/*
	tmp = glob.envi;
	glob.envi = malloc(sizeof(t_envi));
	glob.envi->path = ft_strdup(tochar(data, '='));
	glob.envi->name = ft_strdup(data);
	glob.envi->next = tmp;
	printf("%s\n",glob.envi->name);
	*/
}

void	environnement(char **environnement)
{
	int		i;

	i = 1;
	glob.envi = malloc(sizeof(t_envi));
	glob.envi->path = ft_strdup(tochar(environnement[0], '='));
	glob.envi->name = ft_strdup(environnement[0]);
	glob.envi->next = NULL;
	while (environnement[i])
	{
		add_new(environnement[i]);
		i++;
	}
}
