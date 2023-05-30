/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:07:53 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:07:54 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	quote_error(char *line, int *i, char quote)
{
	while (line[++(*i)] && line[*i] != quote)
		;
	if (!line[*i])
	{
		if (quote == '\"')
			err_msg(1, "Unclosed dquote detected!!!");
		else
			err_msg(1, "Unclosed quote detected!!!");
		return (1);
	}
	return (0);
}

int	check_quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && quote_error(line, &i, '\"'))
			return (1);
		else if (line[i] == '\'' && quote_error(line, &i, '\''))
			return (1);
	}
	return (0);
}

int	check_redirection(t_shell *sh)
{
	char	*line;
	int		i;

	i = 1;
	line = sh->line;
	if (!line[1])
		return (0);
	while (line[i + 1])
	{
		if (err_msg \
		((line[i - 1] == '>' && line[i] == '>' && line[i + 1] == '>') \
		|| (line[i - 1] == '>' && line[i] == '>' && line[i + 1] == '<') \
		|| (line[i - 1] == '>' && line[i] == '<' && line[i + 1] == '>') \
		|| (line[i - 1] == '>' && line[i] == '<' && line[i + 1] == '<') \
		|| (line[i - 1] == '<' && line[i] == '>' && line[i + 1] == '>') \
		|| (line[i - 1] == '<' && line[i] == '>' && line[i + 1] == '<') \
		|| (line[i - 1] == '<' && line[i] == '<' && line[i + 1] == '>') \
		|| (line[i - 1] == '<' && line[i] == '<' && line[i + 1] == '<') \
		, "Syntax error near unexpected token `<' || `>'"))
			return (1);
		i++;
	}
	return (0);
}

int	check_pipes(t_shell *sh)
{
	int	i;

	i = -1;
	sh->pipe_count = 0;
	if (sh->line[0] == '|')
		return (err_msg(1, "Pipe at the start of line"));
	while (sh->line[++i + 1])
	{
		if (sh->line[i] == '|')
		{
			if (sh->line[i - 1] == '|' || sh->line[i + 1] == '|')
				return (err_msg(1, "Pipe error"));
		}
	}
	if (sh->line[i] == '|')
		return (err_msg(1, "Pipe at the end of line"));
	return (0);
}

int	check_pipes_empty(char **spl_pipe)
{
	char	**tmp;
	int		i;

	i = -1;
	while (spl_pipe[++i])
	{
		tmp = split_wout_quotes(spl_pipe[i], ' ');
		err_msg_w_exit(!tmp, 1);
		if (err_msg(!*tmp, "Syntax error near unexpected token `|'"))
		{
			free(tmp);
			return (1);
		}
		double_free(tmp);
	}
	return (0);
}
