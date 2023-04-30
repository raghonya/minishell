#include <minishell.h>

void	clear_quotes_matrix(char **lines)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (lines[i][j] && (lines[i][j] == '\"' || lines[i][j] == '\''))
			{
				k = j-- - 1;
				while (lines[i][++k + 1])
					lines[i][k] = lines[i][k + 1];
				lines[i][k] = 0;
			}
		}
	}
}

// void	clear_quotes_line(char *line)
// {
// 	int	i;
// 	int	k;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		if (line[i] && (line[i] == '\"' || line[i] == '\''))
// 		{
// 			k = i-- - 1;
// 			while (line[++k + 1])
// 				line[k] = line[k + 1];
// 			line[k] = 0;
// 		}
// 	}
// }

void	prompt_and_history(char **line, char **prompt)
{
	*prompt = strjoin_w_free(getcwd(NULL, 0), "$ ");
	*line = readline(*prompt);
	if (!*line)
	{
		printf ("\n");
		//system("leaks minishell");
		exit(0);
	}
	if (!ft_isspace(**line))
		add_history(*line);
}

int	free_and_continue(t_shell *sh)
{
	if (check_line(sh) || check_pipes(sh))
	{
		free(sh->line);
		free(sh->prompt);
		return (1);
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_shell		sh;

	init_env(&sh, envp);
	while (777)
	{
		prompt_and_history(&sh.line, &sh.prompt);
		if (!*sh.line || check_quotes(sh.line))
			continue ;
		sh.line = expand(&sh, sh.line);
		 printf ("ret: %s\n\n", sh.line);
		if (free_and_continue(&sh))
			continue ;
		// t_list *tmp = sh.env;
		// while (tmp)
		// {
		// 	printf ("tmp: %s\n", tmp->data);
		// 	tmp = tmp->next;
		// }

		// check_line(sh);
		// if (check_line(sh));
		// {
		// 	free(sh.line);
		// 	free(sh.prompt);
		// 	continue ;
		// }
		free(sh.prompt);
		free(sh.line);
	}
}
