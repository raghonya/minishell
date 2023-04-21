#include <minishell.h>

int main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	sh->arg->argc = argc;
	sh->arg->argv = argv;
	sh->arg->envp = envp;
	while (777)
	{
		sh->line = readline("minishell$ ");
		sh->line = expand(sh->line, *sh->arg);
		parse_line(sh);
	}
}