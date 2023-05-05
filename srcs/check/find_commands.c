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

void	exec_cmd(char **cmd, int indicator)
{
	int		*pipes;
	int		i;

	
	//i = -1;
	//cmds = split_wout_quotes(line, '|');
	//printf ("\nsplited with '|'\n--------------\n");
	//while (cmds[++i])
	//	;
	//sh->pipe_count = i;
	//	printf ("%s\n", (cmds[i]));
	//printf ("--------------\n");
	// clear_quotes_line(line);
	// printf ("string: %s\n", line);
	//pipes = malloc(sizeof(int) * ((i - 1) * 2));
	//i = -1;
	//while (++i < pipe_count)
	//	err_msg_w_exit(pipe(pipes + (i * 2)) == -1, 1);
	//i = -1;
	//while (++i < pipe_count + 1)
	//	;



	//i = -1;
	//while (++i < pipe_count * 2)
	//	close(pipes[i]);
	//free(pipes);
}

char	**create_envp(t_shell sh)
{
	char	**envp;
	t_list	*head;
	int		size;
	int		i;

	i = -1;
	head = sh.env;
	size = ft_lstsize(sh.env);
	envp = malloc(sizeof(char *) * (size + 1));
	err_msg_w_exit (!envp, 1);
	while (++i < size)
	{
		envp[i] = ft_strdup(head->data);
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);

}

void	exec_one(t_shell *sh)
{
	char		**envp;
	pid_t		cpid;
	int			i;

	envp = create_envp(*sh);
	cpid = fork();
	err_msg_w_exit (cpid == -1, 1);
	if (!cpid)
	{
		err_msg_w_exit(dup2(sh->fdin, 0) == -1, 1);
		err_msg_w_exit(dup2(sh->fdout, 1) == -1, 1);
		find_absolute_path(sh->cmd, sh->paths);
		execve(*sh->cmd, sh->cmd, envp);
		err_msg_w_exit(1, 1);
	}
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	waitpid(cpid, &sh->status, 0);
	sh->exit_stat = WEXITSTATUS(sh->status);
}

void	one_cmd(t_shell *sh)
{
	int	j;

	if (check_redirections(sh, ft_strdup(sh->spl_pipe[0])))
		return ;
	sh->cmd = split_wout_quotes(sh->spl_pipe[0], ' ');
	err_msg_w_exit(!sh->cmd, 1);
	clear_quotes_matrix(sh->cmd);
	// j = -1;
	// printf ("\nspl line wth spaces 1 hati hamar\n");
	// while (sh->cmd[++j])
	// 	printf ("'%s'\n", sh->cmd[j]);
	// printf ("\n");
	if (!ft_strcmp(*sh->cmd, "echo"))
		builtin_echo(sh, sh->cmd);
	else if (!ft_strcmp(*sh->cmd, "cd"))
		builtin_cd(sh, sh->cmd, sh->env);
	else if (!ft_strcmp(*sh->cmd, "pwd"))
		builtin_pwd(sh);
	else if (!ft_strcmp(*sh->cmd, "export"))
		builtin_export(sh, sh->cmd);
	else if (!ft_strcmp(*sh->cmd, "unset"))
		builtin_unset(sh, sh->cmd, &sh->env);
	else if (!ft_strcmp(*sh->cmd, "env"))
		builtin_env(sh, sh->env);
	else if (!ft_strcmp(*sh->cmd, "exit"))
		builtin_exit(sh, sh->cmd);
	else
		exec_one(sh);
	j = -1;
	while (sh->cmd[++j])
		free(sh->cmd[j]);
	free(sh->cmd);
	// return (0);
}

void	multipipes(t_shell *sh)
{
	int	i;
	int	j;

	sh->pipe = malloc(sizeof(int) * (sh->pipe_count * 2));
	err_msg_w_exit(!sh->pipe, 1);
	i = -1;
	while (sh->spl_pipe[++i])
	{
		if (check_redirections(sh, ft_strdup(sh->spl_pipe[0])))
			return ;
		printf ("splited line wth pipes: %s\n", sh->spl_pipe[i]);
		sh->cmd = split_wout_quotes(sh->spl_pipe[i], ' ');
		err_msg_w_exit(!sh->cmd, 1);
		clear_quotes_matrix(sh->cmd);
		j = -1;
		printf ("\nspl line wth spaces\n");
		while (sh->cmd[++j])
			printf ("%s\n", sh->cmd[j]);
		printf ("\n");
		if (!ft_strcmp(*sh->cmd, "echo"))
			builtin_echo(sh, sh->cmd);
		else if (!ft_strcmp(*sh->cmd, "cd"))
			builtin_cd(sh, sh->cmd, sh->env);
		else if (!ft_strcmp(*sh->cmd, "pwd"))
			builtin_pwd(sh);
		else if (!ft_strcmp(*sh->cmd, "export"))
			builtin_export(sh, sh->cmd);
		else if (!ft_strcmp(*sh->cmd, "unset"))
			builtin_unset(sh, sh->cmd, &sh->env);
		else if (!ft_strcmp(*sh->cmd, "env"))
			builtin_env(sh, sh->env);
		else if (!ft_strcmp(*sh->cmd, "exit"))
			builtin_exit(sh, sh->cmd);
		else
		{
			exec_cmd(sh->cmd, i);
		}
		j = -1;
		while (sh->cmd[++j])
			free(sh->cmd[j]);
		free(sh->cmd);
	}
}

int	check_line(t_shell *sh)
{
	int	*pipes;
	int	i;
	int	j;

	i = -1;
	j = -1;

	sh->spl_pipe = split_wout_quotes(sh->line, '|');
	err_msg_w_exit(!sh->spl_pipe, 1);
	while (sh->spl_pipe[++i])
		;
	sh->pipe_count = i - 1;
	if (sh->pipe_count == 0)
		one_cmd(sh);
	else
	{
		multipipes(sh);
	}

	// sh->cmd = split_wout_quotes(sh->line, ' ');
	// if (check_redirections(sh, ft_strdup(sh->line)))
	// 	return (1);
	// printf ("\nsplited\n--------------\n");
	// while (sh->cmd[++i])
	// 	printf ("%s\n", (sh->cmd[i]));
	// printf ("--------------\n");
	// i = -1;
	// red = split_wout_quotes(sh->line, '<');
	// err_msg_w_exit(!sh->cmd, 1);
	// printf ("\nsplited w < \n--------------\n");
	// while (red[++i])
	// 	printf ("%s\n", (red[i]));
	// printf ("--------------\n");

	// clear_quotes_matrix(sh->cmd);

	// i = -1;
	// printf ("\nsplited wout quotes\n--------------\n");
	// while (sh->cmd[++i])
	// 	printf ("%s\n", (sh->cmd[i]));
	// printf ("--------------\n");
	//i  = -1;
	// if (!ft_strcmp(*sh->cmd, "echo"))
	// 	return (builtin_echo(sh->cmd));
	// if (!ft_strcmp(*sh->cmd, "cd"))
	// 	return (builtin_cd(sh->cmd, sh->env));
	// else if (!ft_strcmp(*sh->cmd, "pwd"))
	// 	return (builtin_pwd());
	// else if (!ft_strcmp(*sh->cmd, "export"))
	// 	return (builtin_export(sh->cmd, sh));
	// else if (!ft_strcmp(*sh->cmd, "unset"))
	// 	return (builtin_unset(sh->cmd, &sh->env));
	// else if (!ft_strcmp(*sh->cmd, "env"))
	// 	return (builtin_env(sh->env));
	// else if (!ft_strcmp(*sh->cmd, "exit"))
	// 	return (builtin_exit(sh->cmd));
	// else
	// 	return (0);
	// i = -1;
	return (0);
}

//	echo >a >b >c  -n >d >e >f  barev >a iuytresdfghj