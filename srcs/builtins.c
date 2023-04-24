#include <minishell.h>

void	builtin_echo(char **cmds)
{
	// char	**to_print;
	int		i;

	i = 0;
	if (!ft_strcmp(cmds[++i], "-n"))
		while (cmds[++i])
			printf ("%s ", cmds[i]);
	else
	{
		while (cmds[i])
			printf ("%s ", cmds[i++]);
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

void	builtin_export(t_shell *sh)
{
	char	**add;
	int 	i;

	i = -1;
	add = ft_split(sh->line, ' ');
	err_msg_w_exit(!add, 1);
	while (*add)
	{
		if (!ft_strchr(*add, '=') || ft_isdigit(**add))
		{
			add++;
			continue ;
		}
		while ((*add)[++i])
			if (!ft_isalpha((*add)[i]) && !ft_isdigit((*add)[i]) \
				&& (*add)[i] != '_')
				break ;
		if (ft_strlen(*add) == (size_t)i)
			ft_lstadd_back(&sh->env, ft_lstnew(*add++));
	}
}

void	builtin_env(t_list *env)
{
	while (env)
	{
		printf ("%s\n", env->data);
		env = env->next;
	}
}