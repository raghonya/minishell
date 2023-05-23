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

void	exec_one(t_shell *sh)
{
	char		**envp;
	pid_t		cpid;

	envp = envp_for_execve(*sh);
	find_absolute_path(sh->cmd, sh->paths);
	cpid = fork();
	if (err_msg (cpid == -1, "Fork error"))
		return ;
	if (!cpid)
	{
		printf ("ste es\n");
		sh->sig.sa_handler = SIG_DFL;
		err_msg_w_exit(dup2(sh->fdin, 0) == -1, 1);
		err_msg_w_exit(dup2(sh->fdout, 1) == -1, 1);
		if (sh->here_closer)
			close(sh->heredoc[0]);
		execve(*sh->cmd, sh->cmd, envp);
		err_msg_w_exit(1, 127);
	}
	double_free(envp);
	waitpid(cpid, &sh->status, 0);
	define_exit_stat(sh);
}

int	one_cmd(t_shell *sh)
{
	if (redirections(sh, &sh->spl_pipe[0]))
		return (1);
	sh->cmd = split_wout_quotes(sh->spl_pipe[0], ' ');
	err_msg_w_exit(!sh->cmd, 1);
	clear_quotes_matrix(sh->cmd);
	find_and_execute_1(sh);
	if (sh->here_closer)
		close(sh->heredoc[0]);
	double_free(sh->cmd);
	return (0);
}
