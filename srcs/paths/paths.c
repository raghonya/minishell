/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:47 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/10 16:56:50 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**paths_finder(t_list *envp)
{
	char	**paths;

	while (envp && ft_strncmp(envp->data, "PATH=", 5))
		envp = envp->next;
	if (!envp)
		return (NULL);
	paths = ft_split(envp->data + 5, ':');
	err_msg_w_exit(!paths, 1);
	return (paths);
}

char	*path_check(char **paths, char *cmd)
{
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, cmd);
		if (!access (tmp, X_OK))
		{
			free(cmd);
			return (tmp);
		}
		free(tmp);
		paths++;
	}
	return (cmd);
}

void	find_absolute_path(char **args, char **paths)
{
	char	*tmp;

	if (*args && !ft_strchr(*args, '/') && paths)
	{
		tmp = ft_strjoin("/", *args);
		err_msg_w_exit (!tmp, 1);
		free(*args);
		*args = path_check(paths, tmp);
	}
}
