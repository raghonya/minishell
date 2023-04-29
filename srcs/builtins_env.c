#include <minishell.h>

void	export_w_no_arg(t_list *env)
{
	char	*str;
	char	*tmp;
	int		i;
	int		k;

	while (env)
	{
		str = malloc(ft_strlen(env->data) + 3);
		i = -1;
		k = 0;
		while (env->data[++i] != '=')
			str[k++] = env->data[i];
		str[k++] = '=';
		str[k++] = '\"';
		while (env->data[++i])
			str[k++] = env->data[i];
		str[k++] = '\"';
		str[k] = 0;
		tmp = ft_strjoin("declare -x ", str);
		printf ("%s\n", tmp);
		free(str);
		free(tmp);
		env = env->next;
	}
}

int	builtin_export(char **add, t_shell *sh)
{
	int		i;

	if (!add[1])
		export_w_no_arg(sh->env);
	else
	{
		while (*add)
		{
			if (!ft_strchr(*add, '=') || ft_isdigit(**add) || **add == '=')
			{
				add++;
				continue ;
			}
			i = -1;
			while ((*add)[++i] && (*add)[i] != '=')
				if (!ft_isalpha((*add)[i]) && !ft_isdigit((*add)[i]) \
					&& (*add)[i] != '_')
					break ;
			if ((*add)[i] && (*add)[i] == '=')
				ft_lstadd_back(&sh->env, ft_lstnew(*add++));
		}
	}
	return (0);
}

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
