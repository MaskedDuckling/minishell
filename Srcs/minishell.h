#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>


typedef struct	s_command
{
	char    **argv;
	char    **environ;
	char    *path_to_command;
	char	*input;
	char	*output;
}               t_command;

typedef struct s_envi
{
	char	*path;
	char	*name;
	struct s_envi	*envi;
}				t_envi;

typedef struct	s_word
{
	char			*cont;
	struct s_word	*next;
}				t_word;

char		**ft_split(char const *s, char c);
void		split_command(char **tab);
int			ft_strend_is(char *str, char *end);
int			ft_strlen(char *s);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
t_command	*parsing(char *line, char **environ);
char		**split_line(char *command);
char		*for_access(char *cmd, char **environ);

void		free_command(char **command);
void		init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first));


#endif
