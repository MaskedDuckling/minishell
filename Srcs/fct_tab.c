#include "minishell.h"

int	skip(char *str, int i, t_command *com)
{
	printf("skip\n");
	(void)str;
	(void)com;
	return(i++);
}

int	alpha_num(char *str, int i, t_command *com)
{
	printf("alpha_num\n");
	while (str[i] > 'a' && str[i] < 'z')
		i++;
	(void)com;
	return(i++);
}
int	input(char *str, int i, t_command *com)
{
	printf("input\n");
	(void)str;
	(void)com;
	return(i++);
}
int	output(char *str, int i, t_command *com)
{
	printf("output\n");
	(void)str;
	(void)com;
	return(i++);
}

int	string(char *str, int i, t_command *com)
{
	printf("output");
	(void)str;
	(void)com;
	return(i++);
}

void	init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com))
{
	int	i;

	i = 0;
	while (i < 128)
		fct_tab[i] = skip;
	i = 'A';
	while (i <= 'Z')
		fct_tab[i++] = alpha_num;
	i = 'a';
	while (i <= 'z')
		fct_tab[i++] = alpha_num;
	 i = '0';
	while (i <= '9')
		fct_tab[i++] = alpha_num;
	fct_tab['<'] = input;
	fct_tab['>'] = output;
	fct_tab['"'] = string;
}
