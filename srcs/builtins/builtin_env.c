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
		printf ("%s\n", env->data);
		env = env->next;
	}
	return (0);
}