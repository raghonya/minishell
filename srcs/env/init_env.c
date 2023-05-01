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

void	init_env(t_shell *sh, char **envp)
{
	int	i;

	i = -1;
	sh->env = NULL;
	while (envp[++i])
		ft_lstadd_back(&sh->env, ft_lstnew(ft_strdup(envp[i])));
}
