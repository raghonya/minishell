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


long long	ft_atoll(char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	if (err_msg(ft_strlen(str) > 19, "numeric argument required"))
		exit (255);
	while (ft_isdigit(*str))
		num = num * 10 + (*(str++) - 48);
	if (sign == -1 && num == LONG_MIN)
		return (sign * num);
	if (err_msg(num > LONG_MAX, "numeric argument required"))
		exit (255);
	return (sign * num);
}


int	builtin_exit(t_shell *sh, char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		if (err_msg(i > 1, "exit: Too many arguments"))
			return (1);
	if (cmds[1])
		exit(ft_atoll(cmds[1]) % 256);
	exit(0);
	return (0);
}
