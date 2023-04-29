#include <minishell.h>

void	init_env(t_shell *sh, char **envp)
{
	int	i;

	i = -1;
	sh->env = NULL;
	while (envp[++i])
		ft_lstadd_back(&sh->env, ft_lstnew(ft_strdup(envp[i])));
}