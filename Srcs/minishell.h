#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_envi
{
	char	*path;
	char	*name;
	struct s_envi	*next;
}				t_envi;

typedef struct	s_command
{
	char    **argv;
	t_envi	*envi;
	char	*input;
	char	*output;
}				t_command;

typedef struct	s_word
{
	char			*cont;
	struct s_word	*next;
}				t_word;

typedef struct	s_venv_quotes
{
	t_word	*first;
	int		s;
	int		e;
}				t_venv_quotes;

/*Libft*/
char		**ft_split(char const *s, char c);
int			ft_strend_is(char *str, char *end);
int			ft_strlen(char *s);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);

/*Parsing*/
void		init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first));
char 		*join_words(t_word *first);
char		**split_line(char *command);
char		*replace_newline(char *command, char c);
t_command	*parsing(char *line, t_envi *envi);
t_command	*split_command(char **tab, t_envi *envi);

/*Execution*/
char		*for_access(char *cmd, char **environ);
void		add_new(t_envi **envi, char *data);
char		**join_envi(t_envi *envi);
t_envi		*environnement(char **environnement);
void		free_command(char **command);
void		exec_command(t_command *commands);

/*builtins*/
void		ft_env(t_envi *envi);
void		ft_cd(char *path);
void		ft_unset(t_envi **envi, char *var_name);
void		ft_export(t_envi **envi, char *new_env);
int			ft_pwd(void);
void		ft_echo(char **argv);

#endif
