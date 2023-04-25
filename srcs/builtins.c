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

int	builtin_cd(char **cmds)
{
	int	ret;
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (err_msg (i == 2, "cd: string not in pwd") \
			|| err_msg(i > 2, "too many arguments"))
			return (1);
	}
	ret = chdir(cmds[1]);
	return (0);
}

int	builtin_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf ("%s\n", tmp);
	free(tmp);
	return (0);
}

int	builtin_exit(void)
{
	return (0);
}
