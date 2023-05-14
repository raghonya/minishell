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
	int			i;

	(void)indicator;
	envp = create_envp(*sh);
	find_absolute_path(sh->cmd, sh->paths);
	cpid = fork();
	if (err_msg (cpid == -1, "Fork error"))
		return (1);
	if (!cpid)
	{
		err_msg_w_exit(dup2(sh->fdin, 0) == -1, 1);
		err_msg_w_exit(dup2(sh->fdout, 1) == -1, 1);
		if (sh->here_closer)
			close(sh->heredoc[0]);
		execve(*sh->cmd, sh->cmd, envp);
		err_msg_w_exit(1, 1);
	}
	double_free(envp);
	waitpid(cpid, &sh->status, 0);
	printf ("sh->status: %d\n", sh->status);
	sh->exit_stat = WEXITSTATUS(sh->status);
	printf ("exit stat: %d\n", sh->exit_stat);
	return (0);
}

// exit status when execve fails X
int	one_cmd(t_shell *sh)
{
	int	ret;
	int	j;

	ret = 0;
	if (redirections(sh, &sh->spl_pipe[0]))
		return (1);
	sh->cmd = split_wout_quotes(sh->spl_pipe[0], ' ');
	err_msg_w_exit(!sh->cmd, 1);
	printf ("\nspl line wth spaces 1 hati hamar\n");
	j = -1;
	while (sh->cmd[++j])
		printf ("'%s'\n", sh->cmd[j]);
	printf ("\n");
	clear_quotes_matrix(sh->cmd);
	ret = call_commands(sh, -1, &exec_one);
	if (sh->here_closer)
		close(sh->heredoc[0]);
	double_free(sh->cmd);
	return (ret);
}
