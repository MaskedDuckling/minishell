#include "minishell.h"

char	*tochar(char *s1, char c)
{
	int i;

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

int		envi_len(t_envi *envi)
{
	int i;

	i = 0;
	while (envi)
	{
		envi = envi->next;
		i++;
	}
	return (i);
}

char	**join_envi(t_envi *envi)
{
	char **ret;
	int i;
	int j;

	j = 0;
	i = envi_len(envi);
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	while (j < i)
	{
		ret[j] = ft_strjoin(envi->name, "=");
		ret[j] = ft_strjoin_free(ret[j], envi->path);
		envi = envi->next;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

char	*src_envi(t_envi *envi, char *var_name)
{
	while (envi)
	{
		if (ft_strcmp(envi->name, var_name) == 0)
			return (envi->path);
		envi = envi->next;
	}
	return (NULL);
}

char    *ft_strdup(const char *s1)
{
	char    *new;
	int        i;
	int        len;

	len = 0;
	while (s1[len])
		len++;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	new[i] = '\0';
	return (new);
}

void	add_new(t_envi **envi, char *data)
{
	int		i;
	t_envi *tmp;

	i = 0;
	tmp = *envi;
	*envi = malloc(sizeof(t_envi));
	(*envi)->path = ft_strdup(tochar(data, '='));
	while (data[i])
		i++;
	(*envi)->name = ft_strdup(data);
	(*envi)->next = tmp;
}

t_envi	*environnement(char **environnement)
{
	t_envi *envi = NULL;
	int i = 0;

	while (environnement[i])
	{
		add_new(&envi,environnement[i]);
		i++;
	}
	return (envi);
}