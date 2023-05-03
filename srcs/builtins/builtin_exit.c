/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:07:10 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:07:38 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_exit(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		if (err_msg(i > 1, "exit: Too many arguments"))
			return (1);
	if (cmds[1])
		exit(ft_atoi(cmds[1]) % 256);
	exit(0);
	return (0);
}
