/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:12:02 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:08:58 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	put_value(t_strs *str, char **line, int dollar_index, t_list *env)
{
	int	length;

	length = 0;
	str->until_dlr = ft_substr(*line, 0, dollar_index);
	str->tmp = varname(*line + dollar_index + 1, &length);
	err_msg_w_exit (!str->tmp || !str->until_dlr, 1);
	str->part = strjoin_w_free(str->part, str->until_dlr);
	err_msg_w_exit (!str->part, 1);
	if (!*str->tmp)
		*line += dollar_index + length + 1;
	else
		*line += dollar_index + ft_strlen(str->tmp) + 1;
	str->part = strjoin_w_free(str->part, check_env(str->tmp, env, length));
	err_msg_w_exit (!str->part, 1);
}

void	create_line(char **line, t_list *env, t_strs *str)
{
	int	dollar_index;

	dollar_index = find_dollar(*line);
	if (dollar_index == -1)
	{
		str->part = ft_strdup(*line);
		err_msg_w_exit (!str->part, 1);
		return ;
	}
	str->part = NULL;
	while (dollar_index != -1)
	{
		put_value(str, line, dollar_index, env);
		free(str->until_dlr);
		free(str->tmp);
		dollar_index = find_dollar(*line);
	}
	str->part = strjoin_w_free(str->part, *line);
	err_msg_w_exit (!str->part, 1);
}

void	before_quotes(t_shell *sh, char *line, int *i, int *j)
{
	char	*until_quote;

	while (line[++(*j)] && line[(*j)] != '\"' && line[(*j)] != '\'')
		;
	until_quote = ft_substr(line, *i, *j - *i);
	err_msg_w_exit(!until_quote, 1);
	sh->str.to_free = until_quote;
	*i = *j;
	create_line(&until_quote, sh->env, &sh->str);
	sh->str.ret_str = strjoin_w_free(sh->str.ret_str, sh->str.part);
	err_msg_w_exit(!sh->str.ret_str, 1);
	free(sh->str.to_free);
	free(sh->str.part);
}

void	in_qoutes(t_shell *sh, char *line, int *i, int *j)
{
	char	*in_quote;

	while (line[++(*j)] != line[*i])
		;
	in_quote = ft_substr(line, *i, *j - *i + 1);
	err_msg_w_exit(!in_quote, 1);
	sh->str.to_free = in_quote;
	if (line[*i] == '\"')
	{
		create_line(&in_quote, sh->env, &sh->str);
		sh->str.ret_str = strjoin_w_free(sh->str.ret_str, sh->str.part);
		free(sh->str.part);
	}
	else
		sh->str.ret_str = strjoin_w_free(sh->str.ret_str, in_quote);
	err_msg_w_exit(!sh->str.ret_str, 1);
	free(sh->str.to_free);
	*i = *j;
}

char	*expand(t_shell *sh, char *line)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (find_dollar(line) == -1)
		return (line);
	sh->str.ret_str = NULL;
	while (line[++i])
	{
		before_quotes(sh, line, &i, &j);
		if (!line[j])
			break ;
		in_qoutes(sh, line, &i, &j);
	}
	return (sh->str.ret_str);
}
