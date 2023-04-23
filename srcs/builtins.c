#include <minishell.h>

void	builtin_echo(char *line, char *cmd)
{
	char	**to_print;
	int		i;

	i = -1;
	while (ft_isspace(*line))
		line++;
	to_print = ft_split(line, ' ');
	err_msg_w_exit(!to_print, 1);
	if (!ft_strcmp(to_print[++i], "-n"))
		while (to_print[++i])
			printf ("%s ", to_print[i]);
	else
	{
		while (to_print[i])
			printf ("%s ", to_print[i++]);
		printf ("\n");
	}
	i = -1;
	while (to_print[++i])
		free(to_print[i]);
	free(to_print);
}


//echo "-"n barev
//echo "-n barev"

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