/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:07:06 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:07:06 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_env(t_shell *sh, t_list *env)
{
	while (env)
	{
		if (*env->data != '?')
			ft_putendl_fd (env->data, sh->fdout);
		env = env->next;
	}
	return (0);
}
