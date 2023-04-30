#include <minishell.h>

int	builtin_env(t_list *env)
{
	while (env)
	{
		printf ("%s\n", env->data);
		env = env->next;
	}
	return (0);
}
