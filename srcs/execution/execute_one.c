/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:11:53 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/13 17:11:53 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_one(t_shell *sh, int indicator)
{
	char		**envp;
	pid_t		cpid;

	(void)indicator;
	envp = create_envp(*sh);
	find_absolute_path(sh->cmd, sh->paths);
	sh->child_checker = getpid();
	cpid = fork();
	if (err_msg (cpid == -1, "Fork error"))
		return (1);
	if (!cpid)
	{
		sh->sig.sa_handler = SIG_DFL;
		err_msg_w_exit(dup2(sh->fdin, 0) == -1, 1);
		err_msg_w_exit(dup2(sh->fdout, 1) == -1, 1);
		if (sh->here_closer)
			close(sh->heredoc[0]);
		execve(*sh->cmd, sh->cmd, envp);
		err_msg_w_exit(1, 1);
	}
	sh->child_checker = 0;
	double_free(envp);
	waitpid(cpid, &sh->status, 0);
	define_exit_stat(sh);
	return (0);
}

// exit status when execve fails X
int	one_cmd(t_shell *sh)
{
	int	ret;

	if (redirections(sh, &sh->spl_pipe[0]))
		return (1);
	sh->cmd = split_wout_quotes(sh->spl_pipe[0], ' ');
	err_msg_w_exit(!sh->cmd, 1);
	clear_quotes_matrix(sh->cmd);
	ret = call_commands(sh, -1, &exec_one);
	if (sh->here_closer)
		close(sh->heredoc[0]);
	double_free(sh->cmd);
	return (ret);
}
