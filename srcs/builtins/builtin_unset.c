/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:07:27 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:07:28 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	delete_var(t_list **tmp_prev, t_list **env, t_list **head)
{
	t_list	*tmp;

	tmp = (*env)->next;
	if (*head == *env)
		*head = tmp;
	free((*env)->data);
	free(*env);
	*env = tmp;
	if ((*tmp_prev))
		(*tmp_prev)->next = *env;
	return (1);
}

int	validation(char *var, int *ret)
{
	int	i;

	if (var[0] == '?')
		return (1);
	i = -1;
	while (var[++i])
	{
		if (err_msg ((i == 0 && ft_isdigit(var[i])) \
		|| (!ft_isalnum(var[i]) && var[i] != '_'), \
		"not a valid identifier"))
		{
			*ret = 1;
			return (1);
		}
	}
	return (0);
}

void	removing(t_list **env, t_list **tmp_prev, char *cmd)
{
	char	*tmp_str;
	t_list	*head;

	head = *env;
	tmp_str = ft_strjoin(cmd, "=");
	while (*env)
	{
		if (!ft_strncmp((*env)->data, tmp_str, ft_strlen(tmp_str)) \
			&& delete_var(tmp_prev, env, &head))
			break ;
		*tmp_prev = *env;
		*env = (*env)->next;
	}
	*env = head;
	free(tmp_str);
}

int	builtin_unset(t_shell *sh, char **cmds, t_list **env)
{
	t_list	*tmp_prev;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	(void)sh;
	tmp_prev = NULL;
	while (cmds[++i])
	{
		if (validation(cmds[i], &ret))
			continue ;
		removing(env, &tmp_prev, cmds[i]);
	}
	return (ret);
}
