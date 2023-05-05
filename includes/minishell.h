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
	char	*part;
	char	*ret_str;
}	t_strs;

typedef struct s_shell
{
	t_strs	str;
	t_list	*env;
	char	*line;
	char	*prompt;
	char	**spl_pipe;
	char	**cmd;
	char	**paths;
	int		pipe_count;
	int		fdin;
	int		fdout;

}	t_shell;


//	BUILTINS

int		builtin_cd(t_shell *sh, char **cmds, t_list *env);

int		builtin_pwd(t_shell *sh);

int		builtin_env(t_shell *sh, t_list *env);

int		builtin_exit(t_shell *sh, char **cmds);

int		builtin_echo(t_shell *sh, char **cmds);

int		builtin_unset(t_shell *sh, char **cmds, t_list **env);

int		builtin_export(t_shell *sh, char **cmds);

// Error messages

int		err_msg(int a, char *msg);

void	err_msg_w_exit(int a, int code);

// Parsing

char	*parse_line(t_shell *sh);

void	check_symbols(t_shell *sh);

int		check_pipes(t_shell *sh);

int		check_quotes(char *line);

int		check_line(t_shell *sh);

int		check_redirection(t_shell *sh);

void	clear_quotes_matrix(char **lines);

void	clear_quotes_line(char *line);

void	clear_quotes_line(char *line);

char	*until_symb(char *s, char *c);

char	*after_symb(char *s, char c);

char	*strjoin_w_free(char*s1, char *s2);

char	**split_wout_quotes(char *s, char c);

// env and variables

int		find_dollar(char *s);

int		check_varname(char *s);

char	*varname(char *s, int *length);

char	*expand(t_shell *sh, char *line);

void	init_env(t_shell *sh, char **env);

char	*check_env(char *line, t_list *env, int length);

// Paths

char	**paths_finder(t_list *envp);

char	*path_check(char **paths, char *cmd);

void	find_absolute_path(char **args, char **paths);

// Redirections

int	check_redirections(t_shell *sh, char *line);


//void	free_2d(char **s);

//void	to_close(int *pipefd, t_args arg);

//void	err_msh(int a, int *pipes, t_args arg);

//char	**paths_finder(char **envp);

//char	*path_check(char **paths, char *cmd);

//void	find_absolute_path(char **args, char **paths);

//void	multipipes(t_args arg, char **paths);

//void	here_doc(t_args arg, char **paths);


#endif 