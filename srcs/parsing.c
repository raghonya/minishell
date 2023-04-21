#include <minishell.h>
#include <sys/wait.h>

char	*parse_line(t_shell *sh)
{
	int	i;

	i = -1;
	printf ("%s\n", sh->line);
	while (sh->line[++i])
	{
	// 	if (sh->line[i] == '\"')
	// 		// sh->cnt->dquote++;
	// 		check_dquote(sh); 
	// 	else if (sh->line[i] == '\'')
	// 		// sh->cnt->quote++;
	// 		check_quote(sh);
	// 	else if (sh->line[i] == '|')
	// 		// sh->cnt->pipe++;
	// 		check_pipe(sh);
	// 	else if (sh->line[i] == '$')
	// 		// sh->cnt->dlr++;
	// 		check_dollar(sh);
		;
	}
	return  (sh->line);
}