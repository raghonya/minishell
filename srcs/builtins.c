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

int	cd_errors(char **cmds, char **oldpwd)
{
	int		i;

	i = -1;
	while (cmds[++i])
		if (err_msg (i == 2, "cd: string not in pwd") \
			|| err_msg(i > 2, "too many arguments"))
			return (1);
	*oldpwd = strjoin_w_free(getcwd(NULL, 0), "=");
	if (err_msg(chdir(cmds[1]) == -1, "Cant change directory!!!"))
	{
		free(*oldpwd);
		return (1);
	}
	return (0);
}

int	builtin_cd(char **cmds, t_list *env)
{
	char	*oldpwd;
	int		i;

	if (cd_errors(cmds, &oldpwd))
		return (1);
	while (env)
	{
		if (!ft_strncmp(env->data, "OLDPWD=", 7))
		{
			free(env->data);
			env->data = ft_strjoin("OLDPWD=", oldpwd);
		}
		else if (!ft_strncmp(env->data, "PWD=", 4))
		{
			free(oldpwd);
			free(env->data);
			oldpwd = getcwd(NULL, 0);
			env->data = ft_strjoin("PWD=", oldpwd);
		}
		env = env->next;
	}
	free(oldpwd);
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
