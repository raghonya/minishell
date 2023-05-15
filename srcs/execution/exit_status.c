#include <minishell.h>

void	change_exit_stat(t_shell sh, t_list *env)
{
	char	*tmp1;
	char	*tmp2;

	while (env)
	{
		if (!ft_strncmp(env->data, "?=", 2))
		{
			tmp1 = ft_itoa(sh.exit_stat);
			err_msg_w_exit(!tmp1, 1);
			tmp2 = ft_strjoin("?=", tmp1);
			err_msg_w_exit(!tmp2, 1);
			free(tmp1);
			free(env->data);
			env->data = ft_strdup(tmp2);
			err_msg_w_exit(!env->data, 1);
			free(tmp2);
		}
		env = env->next;
	}
}

void	define_exit_stat(t_shell *sh)
{
	if (WIFEXITED(sh->status))
		sh->exit_stat = WEXITSTATUS(sh->status);
	else if (WIFSIGNALED(sh->status))
		sh->exit_stat = WTERMSIG(sh->status) + 128;
}
