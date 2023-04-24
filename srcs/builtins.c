#include <minishell.h>

void	builtin_echo(char **cmds)
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
				printf ("%s ", cmds[i]);
			else
				printf ("%s", cmds[i]);
			i++;
		}
		printf ("\n");
	}
}

void	builtin_cd()
{
	;
}

void	builtin_pwd()
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf ("%s\n", tmp);
	free(tmp);
}

void	builtin_exit(void)
{
	;
}
