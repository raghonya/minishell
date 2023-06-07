/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:12:00 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/13 17:12:01 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	direct_first_last(t_shell *sh, int indicator)
{
	if (indicator == 0)
	{
		err_msg_w_exit(dup2(sh->fdin, 0) == -1, 1);
		if (sh->fdout == 1)
			err_msg_w_exit(dup2(sh->pipe[indicator + 1], 1) == -1, 1);
		else
			err_msg_w_exit(dup2(sh->fdout, 1) == -1, 1);
	}
	else if (indicator == sh->pipe_count)
	{
		if (sh->fdin == 0)
			err_msg_w_exit(dup2(sh->pipe[(indicator - 1) * 2], 0) == -1, 1);
		else
			err_msg_w_exit(dup2(sh->fdin, 0) == -1, 1);
		err_msg_w_exit(dup2(sh->fdout, 1) == -1, 1);
	}
}

void	direct_cmd(t_shell *sh, int indicator)
{
	int	i;

	i = -1;
	if (indicator == 0 || indicator == sh->pipe_count)
		direct_first_last(sh, indicator);
	else
	{
		if (sh->fdin == 0)
			err_msg_w_exit(dup2(sh->pipe[(indicator - 1) * 2], 0) == -1, 1);
		else
			err_msg_w_exit(dup2(sh->fdin, 0) == -1, 1);
		if (sh->fdout == 1)
			err_msg_w_exit(dup2(sh->pipe[(indicator - 1) * 2 + 3], 1) == -1, 1);
		else
			err_msg_w_exit(dup2(sh->fdout, 1) == -1, 1);
	}	
	while (++i < sh->pipe_count * 2)
		close(sh->pipe[i]);
	free(sh->pipe);
}

int	exec_multi(t_shell *sh, int indicator)
{
	char	**envp;
	pid_t	cpid;

	envp = envp_for_execve(*sh);
	if (ft_strcmp(*sh->cmd, "echo") && ft_strcmp(*sh->cmd, "env") \
		&& ft_strcmp(*sh->cmd, "exit") && ft_strcmp(*sh->cmd, "pwd") \
		&& ft_strcmp(*sh->cmd, "unset") && ft_strcmp(*sh->cmd, "cd") \
		&& ft_strcmp(*sh->cmd, "export"))
		find_absolute_path(sh->cmd, sh->paths);
	cpid = fork();
	if (err_msg_w_close (cpid == -1, "Fork error", sh->pipe_count, sh))
	{
		kill_children(sh, indicator);
		return (1);
	}
	if (!cpid)
	{
		direct_cmd(sh, indicator);
		if (sh->here_closer)
			close(sh->heredoc[0]);
		find_and_execute(sh, envp);
	}
	sh->childs_pid[indicator] = cpid;
	double_free(envp);
	return (0);
}

void	wait_for_childs(t_shell *sh)
{
	int	i;

	i = -1;
	while (++i < sh->pipe_count * 2)
		close(sh->pipe[i]);
	free(sh->pipe);
	if (sh->here_closer)
		close(sh->heredoc[0]);
	sh->here_closer = 0;
	i = 0;
	while (i < sh->pipe_count + 1)
		waitpid(sh->childs_pid[i++], &sh->status, 0);
	free(sh->childs_pid);
	define_exit_stat (sh);
}

int	multipipes(t_shell *sh)
{
	int	i;

	i = -1;
	if (init_pipe (sh))
		return (1);
	while (sh->spl_pipe[++i])
	{
		if (redirections(sh, &sh->spl_pipe[i]))
			return (1);
		sh->cmd = split_wout_quotes(sh->spl_pipe[i], ' ');
		err_msg_w_exit(!sh->cmd, 1);
		if (empty_cmd(sh))
			continue ;
		clear_quotes_matrix(sh->cmd);
		if (fork_err_check(sh, i))
			return (1);
		if (sh->here_closer)
			close(sh->heredoc[0]);
		sh->here_closer = 0;
		double_free(sh->cmd);
	}
	wait_for_childs(sh);
	return (0);
}
