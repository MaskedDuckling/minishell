#include "../minishell.h"

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

long int	ft_atoi_long(char *str)
{
	long long int	nbr;
	int				i;
	int				sign;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
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
	return ((long int)nbr);
}
