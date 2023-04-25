#include <minishell.h>

int	builtin_export(t_shell *sh)
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
	return (0);
}

int	builtin_unset(t_shell *sh)
{
	return (0);
}

int	builtin_env(t_list *env)
{
	while (env)
	{
		printf ("%s\n", env->data);
		env = env->next;
	}
	return (0);
}