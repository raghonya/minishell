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

typedef struct s_strs
{
	char	*until_dlr;
	char	*tmp;
	char	*in_dquotes;
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
	t_strs	str;
	t_chars	cnt;
	t_list	*env;
	char	*line;
	char	*prompt;

}	t_shell;


void	err_msg(int a, char *msg);

void	err_msg_w_exit(int a, int code);

char	*parse_line(t_shell *sh);

void	check_symbols(t_shell *sh);

void	check_pipe(t_shell *sh);

int		check_quotes(char *line);

void	check_line(t_shell sh);

void	clear_quotes(char **lines);

void	init_env(t_shell *sh, char **env);

char	*until_symb(char *s, char *c);

char	*after_symb(char *s, char c);

//void	free_2d(char **s);

//void	to_close(int *pipefd, t_args arg);

//void	err_msh(int a, int *pipes, t_args arg);

//char	**paths_finder(char **envp);

//char	*path_check(char **paths, char *cmd);

//void	find_absolute_path(char **args, char **paths);

//void	multipipes(t_args arg, char **paths);

//void	here_doc(t_args arg, char **paths);

int		check_varname(char *s);

char	*expand(char *line, char **env);

char	*strjoin_w_free(char*s1, char *s2);

char	**split_wout_quotes(char *s);

char	*varname(char *s, int *length);

char	*check_env(char *line, char **env, int length);

void	builtin_echo(char **cmds);

void	builtin_export(t_shell *sh);

void	builtin_pwd(void);

void	builtin_env(t_list *env);

void	builtin_cd(void);


#endif 