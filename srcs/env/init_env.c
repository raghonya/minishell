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

void	init_env(t_shell *sh, char **envp)
{
	int	i;

	i = -1;
	sh->env = NULL;
	while (envp[++i])
		ft_lstadd_back(&sh->env, ft_lstnew(ft_strdup(envp[i])));
	if (find_exit_stat(sh->env))
		ft_lstadd_back(&sh->env, ft_lstnew(ft_strdup("?=0")));
	sh->paths = paths_finder(sh->env);
	err_msg_w_exit(!sh->paths, 1);
}
