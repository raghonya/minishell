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


int	check_pipes(t_shell *sh)
{
	int	i;

	i = 0;
	sh->pipe_count = 0;
	if (sh->line[i] == '|')
		return (err_msg(1, "Pipe at the start of line"));
	while (sh->line[++i + 1])
	{
		if (sh->line[i] == '|')
		{
			if (sh->line[i - 1] == '|' || sh->line[i + 1] == '|')
				return (err_msg(1, "Pipe error"));
			sh->pipe_count++;
		}
	}
	if (sh->line[i] == '|')
		return (err_msg(1, "Pipe at the end of line"));
	return (0);
}