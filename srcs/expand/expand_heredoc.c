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

void	put_value_hdoc(t_strs *str, char **line, int dollar_index, t_list *env)
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

void	create_line_heredoc(char **line, t_list *env, t_strs *str)
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
		put_value_hdoc(str, line, dollar_index, env);
		free(str->until_dlr);
		free(str->tmp);
		dollar_index = find_dollar(*line);
	}
	str->part = strjoin_w_free(str->part, *line);
	err_msg_w_exit (!str->part, 1);
}

void	before_quotes_heredoc(t_shell *sh, char *line, int *i, int *j)
{
	char	*until_quote;

	while (line[++(*j)] && line[(*j)] != '\"' && line[(*j)] != '\'')
		;
	until_quote = ft_substr(line, *i, *j - *i);
	err_msg_w_exit(!until_quote, 1);
	sh->str.to_free = until_quote;
	*i = *j;
	create_line_heredoc(&until_quote, sh->env, &sh->str);
	if (*j > 0 && line[*j - 1] == '$' && (line[*j] == '\'' || line[*j] == '\"'))
		sh->str.part[ft_strlen(sh->str.part) - 1] = 0;
	sh->str.ret_str = strjoin_w_free(sh->str.ret_str, sh->str.part);
	err_msg_w_exit(!sh->str.ret_str, 1);
	free(sh->str.to_free);
	free(sh->str.part);
}

void	in_qoutes_heredoc(t_shell *sh, char *line, int *i, int *j)
{
	char	*in_quote;

	while (line[++(*j)] && line[(*j)] != line[*i])
		;
	in_quote = ft_substr(line, *i, *j - *i + 1);
	err_msg_w_exit(!in_quote, 1);
	sh->str.to_free = in_quote;
	create_line_heredoc(&in_quote, sh->env, &sh->str);
	// printf ("str: %s\n", sh->str.part);
	sh->str.ret_str = strjoin_w_free(sh->str.ret_str, sh->str.part);
	free(sh->str.part);
	free(sh->str.to_free);
	err_msg_w_exit(!sh->str.ret_str, 1);
	*i = *j;
}

char	*expand_heredoc(t_shell *sh, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (find_dollar(line) == -1)
		return (line);
	sh->str.ret_str = NULL;
	while (1)
	{
		before_quotes_heredoc(sh, line, &i, &j);
		if (!line[j])
			break ;
		in_qoutes_heredoc(sh, line, &i, &j);
		printf ("i = %d\n", i);
		if (!line[i++])
			break ;
	}
	free(line);
	return (sh->str.ret_str);
}
