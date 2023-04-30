#include <minishell.h>

int	cd_errors(char **cmds, char **oldpwd)
{
	int		i;

	i = -1;
	while (cmds[++i])
		if (err_msg (i == 2 && !cmds[i + 1], "cd: string not in pwd") \
			|| err_msg(i > 2, "too many arguments"))
			return (1);
	*oldpwd = getcwd(NULL, 0);
	if (err_msg(chdir(cmds[1]) == -1, "Cant change directory!!!"))
	{
		free(*oldpwd);
		return (1);
	}
	return (0);
}

char	*find_pwd(t_list *env, char *oldpwd)
{
	static int	count = 1;

	while (env)
	{
		if (!ft_strncmp(env->data, "PWD=", 4))
			return (ft_strdup(after_symb(env->data, '=')));
		env = env->next;
	}
	if (count++ == 1)
		return (ft_strdup(""));
	return (oldpwd);

}

int	cd_init_oldpwd(t_list *env, char *oldpwd)
{
	oldpwd = find_pwd(env, oldpwd);
	while (env)
	{
		if (!ft_strncmp(env->data, "OLDPWD=", 7))
		{
			free(env->data);
			env->data = ft_strjoin("OLDPWD=", oldpwd);
			break ;
		}
		env = env->next;
	}
	if (!env)
		ft_lstadd_back(&env, ft_lstnew(ft_strjoin("OLDPWD=", oldpwd)));
	free(oldpwd);
}

int	builtin_cd(char **cmds, t_list *env)
{
	char	*oldpwd;
	int		i;

	if (cd_errors(cmds, &oldpwd))
		return (1);
	cd_init_oldpwd(env, oldpwd);
	while (env)
	{
		if (!ft_strncmp(env->data, "PWD=", 4))
		{
			free(env->data);
			oldpwd = getcwd(NULL, 0);
			env->data = ft_strjoin("PWD=", oldpwd);
			free(oldpwd);
			break ;
		}
		env = env->next;
	}
	return (0);
}
