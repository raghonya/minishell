/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:07:22 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:07:23 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_pwd(t_shell *sh)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (err_msg (!tmp, "Im tried to show you, but i can`t"))
		return (1);
	ft_putendl_fd (tmp, sh->fdout);
	free(tmp);
	return (0);
}
