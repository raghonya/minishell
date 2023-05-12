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
		execve(*sh->cmd, sh->cmd, envp);
		err_msg_w_exit(1, 1);
	}
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	waitpid(cpid, &sh->status, 0);
	sh->exit_stat = WEXITSTATUS(sh->status);
	return (0);
}

// exit status when execve fails X

int	one_cmd(t_shell *sh)
{
	int	ret;
	int	j;

	ret = 0;
	//printf ("cmd mmd: %s\n", *sh->cmd);
	sh->fdin = 0;
	sh->fdout = 1;
	if (check_redirections(sh, ft_strdup(sh->spl_pipe[0])))
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
	j = -1;
	while (sh->cmd[++j])
		free(sh->cmd[j]);
	free(sh->cmd);
	return (ret);
}
