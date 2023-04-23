#include <minishell.h>

int	quote_error(char *line, int *i, char quote)
{
	while (line[++(*i)] && line[*i] != quote)
				;
	if (!line[*i])
	{
		if (quote == '\"')
			err_msg(1, "Error: unclosed dquote detected!!!");
		else
			err_msg(1, "Error: unclosed quote detected!!!");
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

void	check_pipe(t_shell *sh)
{
	sh->cnt.pipe++;
}

void	check_symbols(t_shell *sh)
{
	// err_msg (sh->cnt.dquote % 2 || sh->cnt.quote % 2, \
	// 	"Error: unclosed quote detected!!!");
	// check_pipe(sh);
}