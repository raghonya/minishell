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
	free(*env);
	*env = tmp;
	if ((*tmp_prev))
		(*tmp_prev)->next = *env;
	return (1);
}

int	builtin_unset(t_shell *sh, char **cmds, t_list **env)
{
	t_list	*head;
	t_list	*tmp_prev;
	char	*tmp_str;
	int		i;

	i = 0;
	tmp_prev = NULL;
	while (cmds[++i])
	{
		if (*cmds[i] == '?')
			continue ;
		head = *env;
		tmp_str = ft_strjoin(cmds[i], "=");
		while (*env)
		{
			if (!ft_strncmp((*env)->data, tmp_str, ft_strlen(tmp_str)) \
				&& delete_var(&tmp_prev, env, &head))
				break ;
			tmp_prev = *env;
			*env = (*env)->next;
		}
		free(tmp_str);
		*env = head;
	}
	return (0);
}
