/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:11:11 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/13 17:11:19 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern char	*g_sigint_exit;

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
	struct sigaction	sig;
	t_strs				str;
	t_list				*env;
	int					child_checker;
	char				*line;
	char				*prompt;
	char				**spl_pipe;
	char				**cmd;
	char				**paths;
	int					*pipe;
	int					heredoc[2];
	int					here_closer;
	int					*childs_pid;
	int					pipe_count;
	int					exit_stat;
	int					status;
	int					fdin;
	int					fdout;

}	t_shell;

void	main_inits(t_shell *sh, char **envp);

// Execution

void	define_exit_stat(t_shell *sh);

void	change_exit_stat(int exit_stat, t_list *env);

void	find_and_execute_1(t_shell *sh);

void	find_and_execute(t_shell *sh, char **envp);

int		one_cmd(t_shell *sh);

int		multipipes(t_shell *sh);

char	**envp_for_execve(t_shell sh);

int		init_pipe(t_shell *sh);

void	exec_one(t_shell *sh);

int		exec_multi(t_shell *sh, int indicator);

//	BUILTINS

int		builtin_cd(t_shell *sh, char **cmds, t_list *env);

int		builtin_pwd(t_shell *sh);

int		builtin_env(t_shell *sh, t_list *env);

int		builtin_exit(char **cmds);

int		builtin_echo(t_shell *sh, char **cmds);

int		builtin_unset(char **cmds, t_list **env);

int		builtin_export(t_shell *sh, char **cmds);

// Error messages and free

void	double_free(char **info);

int		err_msg(int a, char *msg);

void	err_msg_w_exit(int a, int code);

int		fork_err_check(t_shell *sh, int i);

int		err_msg_w_close(int a, char *msg, int count, t_shell *sh);

// Parsing

void	ignore_quotes(char *line, int *i);

void	check_symbols(t_shell *sh);

int		check_pipes(t_shell *sh);

int		check_quotes(char *line);

int		check_line(t_shell *sh);

int		check_redirection(t_shell *sh);

int		check_pipes_empty(char **spl_pipe);

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

char	*expand_heredoc(t_shell *sh, char *line);

char	*expand(t_shell *sh, char *line);

void	init_env(t_shell *sh, char **env);

char	*check_env(char *line, t_list *env, int length);

// Paths

char	**paths_finder(t_list *envp);

char	*path_check(char **paths, char *cmd);

void	find_absolute_path(char **args, char **paths);

// Redirections

char	*new_string(char *line, int start, int end);

char	*heredoc_change(char *line);

int		find_filename(char *line, char **redir, int *index, int here);

char	*clear_redirection(char *line, int start, int end);

int		heredoc_or_append(t_shell *sh, char **line, int i);

int		redirect_io(t_shell *sh, char **line, int i);

int		redirections(t_shell *sh, char **line);

// Signals

void	sig_catcher(t_shell *sh);

void	handle_signals(int signum);

void	kill_children(t_shell *sh, int i);

#endif
