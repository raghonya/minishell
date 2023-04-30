#include <minishell.h>

int	builtin_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf ("%s\n", tmp);
	free(tmp);
	return (0);
}
