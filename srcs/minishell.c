#include <minishell.h>

void	err_msg_w_exit(int a, int code)
{
	if (a)
	{
		perror ("minishell: Error");
		exit (code);
	}
}

int	err_msg(int a, char *msg)
{
	if (a)
	{
		printf ("minishell: Error: %s\n", msg);
		return (1);
	}
	return (0);
}

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

void	clear_quotes_line(char *line)
{
	int	i;
	int	k;

	i = -1;
	while (line[++i])
	{
		if (line[i] && (line[i] == '\"' || line[i] == '\''))
		{
			k = i-- - 1;
			while (line[++k + 1])
				line[k] = line[k + 1];
			line[k] = 0;
		}
	}
}

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
	if (!*sh->line || check_quotes(sh->line) || check_pipes(sh))
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
		if (free_and_continue(&sh))
			continue ;
		sh.line = expand(sh.line, envp);
		if (free_and_continue(&sh))
			continue ;
		check_line(sh);
		// printf ("ret: %s\n\n", sh.line);
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

//if (sh.line[0] && fork() == 0)
//{
//	execve(ft_strjoin("/bin/", ft_split(sh.line, ' ')[0]), ft_split(sh.line, ' '), envp);
//	execve(ft_strjoin("/usr/bin/", ft_split(sh.line, ' ')[0]), ft_split(sh.line, ' '), envp);
//	exit(1);
//}
