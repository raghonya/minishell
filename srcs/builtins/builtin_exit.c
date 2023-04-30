#include <minishell.h>

int	builtin_exit(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		err_msg(i > 1, "exit: Too many arguments");
		return (1);
	}
	if (cmds[1])
		exit(ft_atoi(cmds[1]) % 256);
	else
		exit(0);
	return (0);
}
