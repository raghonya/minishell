/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:06:43 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:07:34 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_home(t_list *env, char **oldpwd)
{
	while (env)
	{
		if (!ft_strncmp(env->data, "HOME=", 5))
		{
			if (err_msg(chdir(after_symb(env->data, '=')) == -1, \
			"Cant change directory!!!"))
			{
				free(*oldpwd);
				return (1);
			}
			return (0);
		}
		env = env->next;
	}
	return (err_msg(!env, "cd: HOME not set"));
}

int	cd_errors(char **cmds, char **oldpwd, t_list *env)
{
	int		i;

	i = -1;
	while (cmds[++i])
		if (err_msg (i == 2 && !cmds[i + 1], "cd: string not in pwd") \
			|| err_msg(i > 2, "too many arguments"))
			return (1);
	*oldpwd = getcwd(NULL, 0);
	if (cmds[1] && err_msg(chdir(cmds[1]) == -1, "Cant change directory!!!"))
	{
		free(*oldpwd);
		return (1);
	}
	else if (!cmds[1])
		return (check_home(env, oldpwd));
	return (0);
}

char	*find_pwd(t_list *env, char *oldpwd)
{
	static int	count = 1;

	while (env)
	{
		if (!ft_strncmp(env->data, "PWD=", 4))
		{
			free(oldpwd);
			return (ft_strdup(after_symb(env->data, '=')));
		}
		env = env->next;
	}
	if (count++ == 1)
	{
		free(oldpwd);
		return (ft_strdup(""));
	}
	return (oldpwd);
}

int	cd_init_oldpwd(t_list **env, char *oldpwd)
{
	t_list	*head;

	head = *env;
	oldpwd = find_pwd(*env, oldpwd);
	while (*env)
	{
		if (!ft_strncmp((*env)->data, "OLDPWD=", 7))
		{
			free((*env)->data);
			(*env)->data = ft_strjoin("OLDPWD=", oldpwd);
			break ;
		}
		*env = (*env)->next;
	}
	if (!*env)
		ft_lstadd_back(&head, ft_lstnew(ft_strjoin("OLDPWD=", oldpwd)));
	free(oldpwd);
	*env = head;
	return (0);
}

int	builtin_cd(t_shell *sh, char **cmds, t_list *env)
{
	char	*oldpwd;

	if (cd_errors(cmds, &oldpwd, env))
		return (1);
	cd_init_oldpwd(&sh->env, oldpwd);
	while (env)
	{
		if (!ft_strncmp(env->data, "PWD=", 4))
		{
			free(env->data);
			oldpwd = getcwd(NULL, 0);
			env->data = ft_strjoin("PWD=", oldpwd);
			free(oldpwd);
			break ;
		}
		env = env->next;
	}
	return (0);
}
