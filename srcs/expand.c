/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:12:02 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/18 20:12:03 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_dollar(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	create_line(char **line, char **env, t_strs *str)
{
	int	dollar_ind;
	int	length;

	dollar_ind = find_dollar(*line);
	while (dollar_ind != -1)
	{
		length = 0;
		str->until_dlr = ft_substr(*line, 0, dollar_ind);
		str->tmp = until_whitespc(*line + dollar_ind + 1, &length);
		err_msg_w_exit (!str->tmp || !str->until_dlr, 1);
		str->ret = strjoin_w_free(str->ret, str->until_dlr);
		err_msg_w_exit (!str->ret, 1);
		if (!*str->tmp)
			*line += dollar_ind + length + 1;
		else
			*line += dollar_ind + ft_strlen(str->tmp) + 1;
		str->ret = strjoin_w_free(str->ret, check_env(str->tmp, env, length));
		err_msg_w_exit (!str->ret, 1);
		free(str->until_dlr);
		free(str->tmp);
		dollar_ind = find_dollar(*line);
	}
	str->ret = strjoin_w_free(str->ret, *line);
	err_msg_w_exit (!str->ret, 1);
}

char	*expand(char *line, char **env)
{
	int		dollar_ind;
	t_strs	str;

	dollar_ind = find_dollar(line);
	if (dollar_ind == -1)
		return (line);
	str.to_free = line;
	str.ret = NULL;
	create_line(&line, env, &str);
	free(str.to_free);
	return (str.ret);
}
