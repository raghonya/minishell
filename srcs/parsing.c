#include <minishell.h>
#include <sys/wait.h>

//char	*parse_line(t_shell *sh)
//{
//	int	i;

//	i = -1;
//	printf ("%s\n", sh->line);
//	while (sh->line[++i])
//	{
//		if (sh->line[i] == '\"')
//		{
//			check_dquote(sh, &i);
//		}
//			// sh->cnt.dquote++;
//		else if (sh->line[i] == '\'')
//			sh->cnt.quote++;
//		else if (sh->line[i] == '|')
//			sh->cnt.pipe++;
//	}
//	check_symbols(sh);
//	return  (sh->line);
//}