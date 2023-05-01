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

void	print_args(char **cmds, int fd, int i)
{
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			ft_putstr_fd(cmds[i++], fd);
			ft_putstr_fd(" ", fd);
		}
		else
			ft_putstr_fd(cmds[i++], fd);
	}
}

int	builtin_echo(char **cmds)
{
	int		i;

	i = 0;
	int	fd = 1;
	if (!ft_strcmp(cmds[++i], "-n"))
		print_args(cmds, fd, i + 1);
	else
	{
		print_args(cmds, fd, i);
		ft_putstr_fd ("\n", fd);
	}
	return (0);
}
