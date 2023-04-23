#include <minishell.h>

int	quote_error(t_shell *sh, int *i, char quote)
{
	while (sh->line[++(*i)] && sh->line[*i] != quote)
				;
	if (!sh->line[*i])
	{
		if (quote == '\"')
			err_msg(1, "Error: unclosed dquote detected!!!");
		else
			err_msg(1, "Error: unclosed quote detected!!!");
		return (1);
	}
	return (0);
}

int	check_quotes(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->line[++i])
	{
		if (sh->line[i] == '\"' && quote_error(sh, &i, '\"'))
			return (1);
		else if (sh->line[i] == '\'' && quote_error(sh, &i, '\''))
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
	// check_quote()
	// check_dquote(sh);
	// check_pipe(sh);
}