/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:07:15 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:07:42 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export_w_no_arg(t_shell sh, t_list *env)
{
	char	*str;
	char	*tmp;
	int		i;
	int		k;

	while (env)
	{
		str = malloc(ft_strlen(env->data) + 3);
		i = -1;
		k = 0;
		while (env->data[++i] != '=')
			str[k++] = env->data[i];
		str[k++] = '=';
		str[k++] = '\"';
		while (env->data[++i])
			str[k++] = env->data[i];
		str[k++] = '\"';
		str[k] = 0;
		tmp = ft_strjoin("declare -x ", str);
		ft_putendl_fd (tmp, sh.fdout);
		free(str);
		free(tmp);
		env = env->next;
	}
}

int	check_var_existence(char *add, t_shell *sh)
{
	char	*tmp;
	t_list	*head;
	int		i;

	i = 0;
	while (add[i] != '=')
		i++;
	tmp = ft_substr(add, 0, i + 1);
	err_msg_w_exit(!tmp, 1);
	if (tmp[0] == '?')
		return (1);
	head = sh->env;
	while (head)
	{
		if (!ft_strncmp(head->data, tmp, ft_strlen(tmp)))
		{
			free(head->data);
			head->data = strjoin_w_free(tmp, after_symb(add, '='));
			return (1);
		}
		head = head->next;
	}
	free(tmp);
	return (0);
}

int	builtin_export(t_shell *sh, char **add)
{
	int		i;

	if (!add[1])
		export_w_no_arg(*sh, sh->env);
	else
	{
		while (*add)
		{
			if (!ft_strchr(*add, '=') || ft_isdigit(**add) \
				|| **add == '=' || check_var_existence(*add, sh))
			{
				add++;
				continue ;
			}
			i = -1;
			while ((*add)[++i] && (*add)[i] != '=')
				if (!ft_isalpha((*add)[i]) && !ft_isdigit((*add)[i]) \
					&& (*add)[i] != '_')
					break ;
			if ((*add)[i] == '=')
				ft_lstadd_back(&sh->env, ft_lstnew(ft_strdup(*add)));
			add++;
		}
	}
	return (0);
}
