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
	printf ("%s\n", tmp);
	free(tmp);
	return (0);
}
