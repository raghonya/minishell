#include <minishell.h>

void	err_msg_w_exit(int a, int code)
{
	if (a)
	{
		perror ("minishell: Error");
		exit (code);
	}
}

void	err_msg(int a, char *msg)
{
	if (a)
	{
		printf ("minishell: %s\n", msg);
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

int main(int argc, char **argv, char **envp)
{
	t_shell		sh;

	init_env(&sh, envp);
	while (777)
	{
		prompt_and_history(&sh.line, &sh.prompt);
		if (check_quotes(sh.line))
		{
			free(sh.line);
			free(sh.prompt);
			continue ;
		}
		sh.line = expand(sh.line, envp);
		printf ("ret: %s\n\n", sh.line);
		check_line(sh);
		//sh.line = clear_quotes(sh.line);
		free(sh.prompt);
		free(sh.line);
	}
}