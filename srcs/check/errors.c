#include <minishell.h>

void	err_msg_w_exit(int a, int code)
{
	if (a)
	{
		perror ("minishell: Error");
		exit (code);
	}
}

int	err_msg(int a, char *msg)
{
	if (a)
	{
		printf ("minishell: Error: %s\n", msg);
		return (1);
	}
	return (0);
}
