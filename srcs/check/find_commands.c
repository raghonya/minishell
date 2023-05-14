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

int	check_pipes_empty(char **spl_pipe)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	while (spl_pipe[++i])
	{
		tmp = split_wout_quotes(spl_pipe[i], ' ');
		err_msg_w_exit(!tmp, 1);
		if (err_msg(!*tmp, "Syntax error near unexpected token `|'"))
		{
			free(tmp);
			return (1);
		}
		double_free(tmp);
	}
	return (0);
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
		err_msg_w_exit(!envp[i], 1);
		head = head->next;
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

int	call_commands(t_shell *sh, int i, int (*execute)(t_shell *, int))
{	
	int	ret;

	if (!ft_strcmp(*sh->cmd, "echo"))
		ret = builtin_echo(sh, sh->cmd);
	else if (!ft_strcmp(*sh->cmd, "cd"))
		ret = builtin_cd(sh, sh->cmd, sh->env);
	else if (!ft_strcmp(*sh->cmd, "pwd"))
		ret = builtin_pwd(sh);
	else if (!ft_strcmp(*sh->cmd, "export"))
		ret = builtin_export(sh, sh->cmd);
	else if (!ft_strcmp(*sh->cmd, "unset"))
		ret = builtin_unset(sh, sh->cmd, &sh->env);
	else if (!ft_strcmp(*sh->cmd, "env"))
		ret = builtin_env(sh, sh->env);
	else if (!ft_strcmp(*sh->cmd, "exit"))
		ret = builtin_exit(sh, sh->cmd);
	else
		return (execute(sh, i));
	sh->exit_stat = ret;
	return (ret);
}

int	check_line(t_shell *sh)
{
	int	*pipes;
	int	ret;
	int	i;
	int	j;

	i = -1;
	j = -1;
	sh->spl_pipe = split_wout_quotes(sh->line, '|');
	err_msg_w_exit(!sh->spl_pipe, 1);
	if (check_pipes_empty(sh->spl_pipe))
		return (1);
	while (sh->spl_pipe[++i])
		;
	sh->pipe_count = i - 1;
	if (sh->pipe_count == 0)
		ret = one_cmd(sh);
	else
		ret = multipipes(sh);
	change_exit_stat(*sh, sh->env);
	return (ret);
}

//	echo >a >b >c  -n >d >e >f  barev >a iuytresdfghj