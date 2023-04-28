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
	int		pipe_count;

}	t_shell;


int		err_msg(int a, char *msg);

void	err_msg_w_exit(int a, int code);

char	*parse_line(t_shell *sh);

void	check_symbols(t_shell *sh);

int		check_pipes(t_shell *sh);

int		check_quotes(char *line);

int		check_line(t_shell sh);

void	clear_quotes_matrix(char **lines);

void	clear_quotes_line(char *line);

void	init_env(t_shell *sh, char **env);

int		find_dollar(char *s);

char	*until_symb(char *s, char *c);

char	*after_symb(char *s, char c);

int		check_varname(char *s);

char	*varname(char *s, int *length);

char	*expand(t_shell *sh, char *line);

char	*strjoin_w_free(char*s1, char *s2);

char	**split_wout_quotes(char *s, char c);

char	*check_env(char *line, t_list *env, int length);

//	BUILTINS

int		builtin_echo(char **cmds);

int		builtin_exit(void);

int		builtin_pwd(void);

int		builtin_cd(char **cmds);

int		builtin_env(t_list *env);

int		builtin_unset(char **cmds, t_list **env);

int		builtin_export(char **cmds, t_shell *sh);

// BUILTINS END

char	**paths_finder(t_list *envp);

char	*path_check(char **paths, char *cmd);

void	find_absolute_path(char **args, char **paths);

//void	free_2d(char **s);

//void	to_close(int *pipefd, t_args arg);

//void	err_msh(int a, int *pipes, t_args arg);

//char	**paths_finder(char **envp);

//char	*path_check(char **paths, char *cmd);

//void	find_absolute_path(char **args, char **paths);

//void	multipipes(t_args arg, char **paths);

//void	here_doc(t_args arg, char **paths);


#endif 