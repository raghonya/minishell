/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:08:07 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:08:07 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**envp_for_execve(t_shell sh)
{
	char	**envp;
	int		size;
	int		i;

	i = -1;
	size = ft_lstsize(sh.env);
	envp = malloc(sizeof(char *) * (size + 1));
	err_msg_w_exit (!envp, 1);
	while (++i < size)
	{
		envp[i] = ft_strdup(sh.env->data);
		err_msg_w_exit(!envp[i], 1);
		sh.env = sh.env->next;
	}
	envp[i] = NULL;
	return (envp);
}
/*
	// indicator: 0 ... pipe_count
	// imagine we have 3 pipes, 4 cmds, and indicator is 0 ... 3

	// sh->pipe = (0 , 1)   (2 , 3)   (4 , 5)
	//             rd  wr    rd  wr    rd  wr

	// indicator = 0, in fdin, out pipe[1]
	// indicator = 1, in pipe[0], out pipe[3]
	// indicator = 2, in pipe[2], out pipe[5]
	// indicator = 3, in pipe[4], out fdout

	//ev ayspes, in pipe[(indicator - 1) * 2], out pipe[(indicator - 1) * 2 + 3];
*/

void	find_and_execute(t_shell *sh, char **envp)
{
	if (!ft_strcmp(*sh->cmd, "echo"))
		exit (builtin_echo(sh, sh->cmd));
	else if (!ft_strcmp(*sh->cmd, "cd"))
		exit (builtin_cd(sh, sh->cmd, sh->env));
	else if (!ft_strcmp(*sh->cmd, "pwd"))
		exit (builtin_pwd(sh));
	else if (!ft_strcmp(*sh->cmd, "export"))
		exit (builtin_export(sh, sh->cmd));
	else if (!ft_strcmp(*sh->cmd, "unset"))
		exit (builtin_unset(sh->cmd, &sh->env));
	else if (!ft_strcmp(*sh->cmd, "env"))
		exit (builtin_env(sh, sh->env));
	else if (!ft_strcmp(*sh->cmd, "exit"))
		exit (builtin_exit(sh->cmd));
	execve(*sh->cmd, sh->cmd, envp);
	ft_putstr_fd ("\033[0;31mminishell: ", 2);
	ft_putstr_fd (*sh->cmd + 1, 2);
	ft_putstr_fd (": command not found\n", 2);
	exit (127);
}

void	find_and_execute_1(t_shell *sh)
{	
	if (!ft_strcmp(*sh->cmd, "echo"))
		sh->exit_stat = builtin_echo(sh, sh->cmd);
	else if (!ft_strcmp(*sh->cmd, "cd"))
		sh->exit_stat = builtin_cd(sh, sh->cmd, sh->env);
	else if (!ft_strcmp(*sh->cmd, "pwd"))
		sh->exit_stat = builtin_pwd(sh);
	else if (!ft_strcmp(*sh->cmd, "export"))
		sh->exit_stat = builtin_export(sh, sh->cmd);
	else if (!ft_strcmp(*sh->cmd, "unset"))
		sh->exit_stat = builtin_unset(sh->cmd, &sh->env);
	else if (!ft_strcmp(*sh->cmd, "env"))
		sh->exit_stat = builtin_env(sh, sh->env);
	else if (!ft_strcmp(*sh->cmd, "exit"))
		sh->exit_stat = builtin_exit(sh->cmd);
	else
		exec_one(sh);
}

//check exit status erb redirection error ka

int	check_line(t_shell *sh)
{
	int	i;

	i = -1;
	sh->paths = paths_finder(sh->env);
	sh->spl_pipe = split_wout_quotes(sh->line, '|');
	err_msg_w_exit(!sh->spl_pipe, 1);
	if (check_pipes_empty(sh->spl_pipe))
		return (1);
	while (sh->spl_pipe[++i])
		;
	sh->pipe_count = i - 1;
	if (sh->pipe_count < 0)
		return (1);
	if (sh->pipe_count == 0)
		return (one_cmd(sh));
	return (multipipes(sh));
}

//	echo >a >b >c  -n >d >e >f  barev >a iuytresdfghj