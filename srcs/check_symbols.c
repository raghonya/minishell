#include <minishell.h>

void	check_dquote(t_shell *sh)
{
	sh->cnt->dquote++;
	
}

void	check_pipe(t_shell *sh, int i)
{
	sh->cnt->pipe++;
}