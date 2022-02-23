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
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_envi
{
	char			*path;
	char			*name;
	struct s_envi	*next;
}				t_envi;

typedef struct s_redi
{
	char			*cont;
	int				type;
	struct s_redi	*next;
}				t_redi;

typedef struct s_glob
{
	t_envi	*envi;
}				t_glob;

typedef struct s_command
{
	char	**argv;
	t_redi	*redi;
	int		check;
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

t_glob glob;

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

/*Parsing*/
void		init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first));
char		*join_words(t_word *first);
char		**split_line(char *command);
char		*replace_newline(char *command, char c);
int			parsing(char *line, t_command **commands);
int			split_command(char **tab, t_command **commands);
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
void		init_fct_tab(int (*fct_tab[128])(char *str, int i, t_command *com, t_word *first));
char		*lch_to_str(t_word	*first);
int			skip(char *str, int i, t_command *com, t_word *first);
int			place_word(t_word *first, char *ret);
char		*cut_word(char *str, int start, int end);
int			redi(t_command *com, char *cont, int type);

/*Redirections*/
void		ft_redi(t_command command);

/*Execution*/
char		*for_access(char *cmd, char **environ);
void		add_new(char *data);
char		**join_envi(void);
void		environnement(char **environnement);
void		free_command(char **command);
void		exec_command(t_command *commands);
int			ft_builtins(t_command command);
char		*src_envi(char *var_name);
void		child_process(t_command command, int *tube, int fd);

/*builtins*/
void		ft_env(void);
void		ft_cd(char *path);
void		ft_unset(char *var_name);
void		ft_export(char *new_env);
int			ft_pwd(void);
void		ft_echo(char **argv);

void		free_process(t_command command);
void		destroy_com(t_command *com);

#endif
