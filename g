/* ************************************************************************** */^M$
/*                                                                            */^M$
/*                                                        :::      ::::::::   */^M$
/*   init_env.c                                         :+:      :+:    :+:   */^M$
/*                                                    +:+ +:+         +:+     */^M$
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */^M$
/*                                                +#+#+#+#+#+   +#+           */^M$
/*   Created: 2023/05/01 13:08:37 by raghonya          #+#    #+#             */^M$
/*   Updated: 2023/05/01 13:08:40 by raghonya         ###   ########.fr       */^M$
/*                                                                            */^M$
/* ************************************************************************** */^M$
^M$
#include <minishell.h>^M$
^M$
void	init_env(t_shell *sh, char **envp)^M$
{^M$
	int	i;^M$
^M$
	i = -1;^M$
	sh->env = NULL;^M$
	while (envp[++i])^M$
		ft_lstadd_back(&sh->env, ft_lstnew(ft_strdup(envp[i])));^M$
}^M$
