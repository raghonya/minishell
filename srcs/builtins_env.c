#include <minishell.h>

int	delete_var(t_list **tmp_prev, t_list **env, t_list **head)
{
	t_list	*tmp;

	tmp = (*env)->next;
	if (*head == *env)
		*head = tmp;
	free(*env);
	*env = tmp;
	if ((*tmp_prev))
		(*tmp_prev)->next = *env;
	return (1);
}

int	builtin_unset(char **cmds, t_list **env)
{
	t_list	*head;
	t_list	*tmp_prev;
	char	*tmp_str;
	int		i;

	i = 0;
	tmp_prev = NULL;
	while (cmds[++i])
	{
		head = *env;
		tmp_str = ft_strjoin(cmds[i], "=");
		while (*env)
		{
			if (!ft_strncmp((*env)->data, tmp_str, ft_strlen(tmp_str)) \
				&& delete_var(&tmp_prev, env, &head))
				break ;
			tmp_prev = *env;
			*env = (*env)->next;
		}
		free(tmp_str);
		*env = head;
	}
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
