/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:08:00 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:08:01 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	err_msg_w_exit(int a, int code)
{
	if (a)
	{
		perror ("minishell: Error");
		exit (code);
	}
}

int	err_msg_w_close(int a, char *msg, int count, t_shell *sh)
{
	int	i;

	i = -1;
	if (a)
	{
		while (++i < count * 2)
			close (sh->pipe[i]);
		free(sh->pipe);
		ft_putstr_fd ("minishell: Error: ", 2);
		ft_putendl_fd (msg, 2);
		return (1);
	}
	return (0);
}

int	err_msg(int a, char *msg)
{
	if (a)
	{
		ft_putstr_fd ("minishell: Error: ", 2);
		ft_putendl_fd (msg, 2);
		return (1);
	}
	return (0);
}
