/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:08:37 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:08:40 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	readline_break(void)
{
	return (0);
}

void	main_inits(t_shell *sh, char **envp)
{
	rl_event_hook = &readline_break;
	init_env(sh, envp);
	sh->line = NULL;
	sh->paths = NULL;
	sh->prompt = NULL;
	sh->exit_stat = 0;
	sig_catcher(sh);
}

int	find_exit_stat(t_list *env)
{
	while (env)
	{
		if (!ft_strncmp(env->data, "?=", 2))
			return (0);
		env = env->next;
	}
	return (1);
}

int	init_pipe(t_shell *sh)
{
	int	i;

	sh->pipe = malloc(sizeof(int) * (sh->pipe_count * 2));
	err_msg_w_exit(!sh->pipe, 1);
	i = -1;
	while (++i < sh->pipe_count)
		if (err_msg_w_close (pipe(sh->pipe + (i * 2)) < 0, "PipError", i, sh))
			return (1);
	sh->childs_pid = malloc(sizeof(int) * (sh->pipe_count + 1));
	err_msg_w_exit(!sh->childs_pid, 1);
	return (0);
}

void	init_env(t_shell *sh, char **envp)
{
	char	*tmp;
	int		i;

	i = -1;
	sh->env = NULL;
	while (envp[++i])
	{
		tmp = ft_strdup(envp[i]);
		err_msg_w_exit (!tmp, 1);
		ft_lstadd_back(&sh->env, ft_lstnew(tmp));
	}
	if (find_exit_stat(sh->env))
		ft_lstadd_back(&sh->env, ft_lstnew(ft_strdup("?=0")));
}
