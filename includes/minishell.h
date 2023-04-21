#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_args
{
	int		fdin;
	int		fdout;
	int		argc;
	char	**argv;
	char	**envp;
}	t_args;

typedef struct s_strs
{
	char	*until_dlr;
	char	*tmp;
	char	*to_free;
	char	*ret;
}	t_strs;

typedef struct s_chars
{
	int	pipe;
	int	quote;
	int	dquote;
	int	dlr; 
}	t_chars;

typedef struct s_shell
{
	t_args *arg;
	t_strs *str;
	t_chars *cnt;
	char *line;

}	t_shell;

char	*parse_line(t_shell *sh);

void	free_2d(char **s);

void	to_close(int *pipefd, t_args arg);

void	err_pipe(int a, int *pipes, t_args arg);

char	**paths_finder(char **envp);

char	*path_check(char **paths, char *cmd);

void	find_absolute_path(char **args, char **paths);

void	multipipes(t_args arg, char **paths);

void	here_doc(t_args arg, char **paths);

char	*expand(char *line, t_args arg, int *pipes);

char	*strjoin_w_free(char*s1, char *s2);

char	*until_whitespc(char *s, int *length);

char	*check_env(char *line, char **env, int length);

#endif 