#include <minishell.h>

int main()
{
	t_shell	sh;
	
	while (777)
	{
		sh.line = readline("minishell$ ");
		parse_line(&sh);
	}
}