#include <minishell.h>

int main(int argc, char **argv, char **envp)
{
	t_shell		sh;
	char	*prompt;

	init_env(&sh, envp);
	while (777)
	{
		prompt = NULL;
		prompt = getcwd(prompt, 0);
		prompt = strjoin_w_free(prompt, "$ ");
		sh.line = readline(prompt);
		if (!sh.line)
		{
			printf ("\n");
			exit(0);
		}
		sh.line = expand(sh.line, envp);
		printf ("%s\n", sh.line);
		free(sh.line);
		free(prompt);
		//parse_line(sh);
	}
}