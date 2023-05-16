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
	int	i;

	i = 0;
	while (envp && ft_strncmp(envp->data, "PATH=", 5))
		envp = envp->next;
	if (!envp)
		return (NULL);
	while (envp->data[i] != '/')
		i++;
	return (ft_split(envp->data + i, ':'));
}

char	*path_check(char **paths, char *cmd)
{
	char	*tmp;

	if (!cmd)
		return (NULL);
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
	int		i;

	i = -1;
	if (*args && !ft_strchr(*args, '/'))
	{
		tmp = ft_strjoin("/", *args);
		free(*args);
		*args = path_check(paths, tmp);
	}
}
