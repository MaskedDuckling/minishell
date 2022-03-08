#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "pars/pars.h"
# include "exec/exec.h"
# include "envi/envi.h"
# include <string.h>
# include <signal.h>

int is_running; 

typedef struct s_envi
{
	char			*name;
	char			*path;
	struct s_envi	*next;
}				t_envi;

typedef struct s_redi
{
	char			*cont;
	int				type;
	struct s_redi	*next;
}				t_redi;

typedef struct s_command
{
	char	**argv;
	t_redi	*redi;
	t_envi	*envi;
	int		check;
	int		exit_status;
	pid_t	pid;
}				t_command;

typedef struct s_word
{
	char			*cont;
	struct s_word	*next;
}				t_word;

typedef struct s_venv_quotes
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
char		*ft_substr(char *s, int start, int len);
int			ft_is_in(char *str, char c);
char		*ft_strndup(const char *s1, int n);

/*Parsing*/
void		init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first));
char		*join_words(t_word *first);
char		**split_line(char *command);
char		*replace_newline(char *command, char c);
int			parsing(char *line, t_command **commands, t_envi *envi, int exit_status);
int			split_command(char **tab, t_command **commands, t_envi *envi, int exit_status);
int			check_line(char *line);

/*tab parsing*/
int			word(char *str, int i, t_command *com, t_word *first);
int			squotes(char *str, int i, t_command *com, t_word *first);
int			dquotes(char *str, int i, t_command *com, t_word *first);
int			alpha_num(char *str, int i, t_command *com, t_word *first);
int			alpha_num_quotes(char *str, int i, t_command *com, t_word *first);
int			input(char *str, int i, t_command *com, t_word *first);
int			output(char *str, int i, t_command *com, t_word *first);
int			venv(char *str, int i, t_command *com, t_word *first);

/*tab parsing utils*/
char		*ft_itoa(int n);
void		init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first));
char		*lch_to_str(t_word	*first);
int			skip(char *str, int i, t_command *com, t_word *first);
int			place_word(t_word *first, char *ret);
char		*cut_word(char *str, int start, int end);
int			redi(t_command *com, char *cont, int type);

/*Redirections*/
void		ft_redi(t_command command);

/*Environ*/
char		*for_access(char *cmd, char **environ);
void		add_new(char *data, t_envi *envi);
char		**join_envi(t_envi *envi);
t_envi		*environnement(char **environnement);

/*Execution*/
void		free_command(char **command);
int			exec_command(t_command *commands);
int			ft_builtins(t_command command);
int			ft_builtins_fork(t_command command, int *tube);
char		*src_envi(char *var_name,t_envi *envi);
void		child_process(t_command command, int *tube, int fd);

/*builtins*/
int			ft_env(int *tube, t_envi *envi, char *argv1);
int			ft_cd(char *path);
int		ft_unset(char *var_name, t_envi *envi);
int		ft_export(char *new_env, t_envi *envi);
int			ft_pwd(int *tube);
int			ft_echo(char **argv, int *tube);
int			is_builtin(t_command command);
int			is_builtin_fork(t_command command);

/*error and free*/
void		destroy_env(t_envi *envi);
int			erroring(int check);
void		free_process(t_command command);
void		destroy_com(t_command *com);

int			sig_init();

#endif
