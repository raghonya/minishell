#include <minishell.h>

int	builtin_echo(char **cmds)
{
	int		i;

	i = 0;
	if (!ft_strcmp(cmds[++i], "-n"))
	{
		while (cmds[++i])
		{
			if (cmds[i + 1])
				printf ("%s ", cmds[i]);
			else
				printf ("%s", cmds[i]);
		}
	}
	else
	{
		while (cmds[i])
		{
			if (cmds[i + 1])
				printf ("%s ", cmds[i++]);
			else
				printf ("%s", cmds[i++]);
		}
		printf ("\n");
	}
	return (0);
}
