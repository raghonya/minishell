#include <minishell.h>

void	check_dquote(t_shell *sh, int *i)
{
	while (sh->line[*i] && sh->line[*i] != '\"')
	{
		*i += 1;
	}
	err_msg(!sh->line[*i], "Error: unclosed quote detected!!!");
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