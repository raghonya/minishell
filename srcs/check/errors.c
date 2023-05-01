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

int	err_msg(int a, char *msg)
{
	if (a)
	{
		printf ("minishell: Error: %s\n", msg);
		return (1);
	}
	return (0);
}
