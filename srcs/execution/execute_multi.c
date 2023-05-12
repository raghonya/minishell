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
	int i;

	i = -1;
	printf ("pipe_count: %d, indicator: %d\n", sh->pipe_count, indicator);
	printf ("fdin: %d, fdout: %d\n", sh->fdin, sh->fdout);
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
	int		i;

	envp = create_envp(*sh);
	find_absolute_path(sh->cmd, sh->paths);
	cpid = fork();
	if (err_msg_w_close (cpid == -1, "Fork error", sh->pipe_count, sh))
		return (1);
	if (!cpid)
	{
		direct_cmd(sh, indicator);
		execve(*sh->cmd, sh->cmd, envp);
		err_msg_w_exit(1, 1);
	}
	sh->childs_pid[indicator] = cpid;
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	return (0);
}

int	multipipes(t_shell *sh)
{
	int	ret;
	int	i;
	int	j;

	ret = 0;
	sh->pipe = malloc(sizeof(int) * (sh->pipe_count * 2));
	err_msg_w_exit(!sh->pipe, 1);
	i = -1;
	while (++i < sh->pipe_count)
		err_msg_w_close (pipe(sh->pipe + (i * 2)) == -1, "Pipe error", i, sh);
	sh->childs_pid = malloc(sizeof(int) * (sh->pipe_count + 1));
	err_msg_w_exit(!sh->childs_pid, 1);
	i = -1;
	while (sh->spl_pipe[++i])
	{
		sh->fdin = 0;
		sh->fdout = 1;
		if (redirections(sh, &sh->spl_pipe[i]))
			return (1);
		// printf ("splited line wth pipes: %s\n", sh->spl_pipe[i]);
		sh->cmd = split_wout_quotes(sh->spl_pipe[i], ' ');
		err_msg_w_exit(!sh->cmd, 1);
		clear_quotes_matrix(sh->cmd);
		// j = -1;
		// printf ("\nspl line wth spaces\n");
		// while (sh->cmd[++j])
		// 	printf ("%s\n", sh->cmd[j]);
		// printf ("\n");
		ret = call_commands(sh, i, &exec_multi);
		j = -1;
		while (sh->cmd[++j])
			free(sh->cmd[j]);
		free(sh->cmd);
	}
	i = -1;
	while (++i < sh->pipe_count * 2)
		close(sh->pipe[i]);
	free(sh->pipe);
	i = 0;
	while (i < sh->pipe_count + 1)
		waitpid(sh->childs_pid[i++], &sh->status, 0);
	sh->exit_stat = WEXITSTATUS(sh->status);
	return (0);
}
