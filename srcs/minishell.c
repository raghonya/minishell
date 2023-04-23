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

int main(int argc, char **argv, char **envp)
{
	t_shell		sh;
	char	*prompt;

	init_env(&sh, envp);
	while (777)
	{
		prompt = NULL;
		prompt = strjoin_w_free(getcwd(prompt, 0), "$ ");
		sh.line = readline(prompt);
		add_history(sh.line);
		if (!sh.line)
		{
			printf ("\n");
			//system("leaks minishell");
			exit(0);
		}
		if (check_quotes(&sh))
		{
			free(sh.line);
			free(prompt);
			continue ;
		}
		sh.line = expand(sh.line, envp);
		free(prompt);
		free(sh.line);
	}
}