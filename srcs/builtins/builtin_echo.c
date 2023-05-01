/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:06:52 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:06:53 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_echo(char **cmds)
{
	int		i;

	i = 0;
	if (!ft_strcmp(cmds[++i], "-n"))
	{
		while (cmds[++i])
		{
			if (cmds[i + 1])
				printf ("%s ", cmds[i]);
			else
				printf ("%s", cmds[i]);
		}
	}
	else
	{
		while (cmds[i])
		{
			if (cmds[i + 1])
				printf ("%s ", cmds[i++]);
			else
				printf ("%s", cmds[i++]);
		}
		printf ("\n");
	}
	return (0);
}
